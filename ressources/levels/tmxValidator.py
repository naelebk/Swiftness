import xml.etree.ElementTree as ET
import sys

class TmxValidator:
    def __init__(self, file_path):
        self.file_path = file_path
        self.errors = []

        # Expected tilesets
        self.expected_tilesets = {
            "01_utilities.tsx": 1,
            "02_portal.tsx": 3,
            "03_futuristic_city.tsx": 27,
            "04_gravity_switch.tsx": 51,
            "05_gravity_flow.tsx": 67,
            "06_wall_of_death.tsx": 79,
            "07_gravity_walls.tsx": 95,
            "08_gravity_walls_open.tsx": 143,
            "09_arrow.tsx": 191,
            "10_alpha.tsx": 195,
            "11_alpha_key.tsx": 225,
        }
        self.expected_layers = [
            "Gw_orange_open", "Gw_green_open", "Gw_rose_open", "Gw_blue_open",
            "Gw_orange", "Gw_green", "Gw_rose", "Gw_blue",
            "gravity_walls", "Decoration", "Filling",
            "gravity_switch", "Collision_bloc", "Collision_h", "Collision_v",
            "Wall_of_death_bloc", "Wall_of_death_h", "Wall_of_death_v", 
            "Border", "IO"
        ]
        self.object_layers = ["gravity_walls", "gravity_switch"]

    def validate(self):
        tree = ET.parse(self.file_path)
        root = tree.getroot()

        # Check tilewidth and tileheight
        tilewidth = int(root.get('tilewidth'))
        tileheight = int(root.get('tileheight'))
        if tilewidth != 16 or tileheight != 16:
            self.errors.append("[ERROR] : tilewidth and tileheight must be 16.")

        self.validate_tilesets(root)
        self.validate_layers(root)

        return self.errors

    def validate_tilesets(self, root):
        tilesets = {tileset.get('source').split('/')[-1]: int(tileset.get('firstgid')) for tileset in root.findall('tileset')}
        for name, gid in self.expected_tilesets.items():
            if name not in tilesets:
                self.errors.append(f"[ERROR] : Tileset '{name}' is missing.")
            elif tilesets[name] != gid:
                self.errors.append(f"[ERROR] : Tileset '{name}' has incorrect GID (expected {gid}, found {tilesets[name]}).")

    def validate_layers(self, root):
        layers = {layer.get('name'): layer for layer in root.findall('.//layer')}
        object_groups = {group.get('name'): group for group in root.findall('.//objectgroup')}
        layer_sizes = []
        tile_counts = []

        for layer_name in self.expected_layers:
            if layer_name in self.object_layers:
                if layer_name not in object_groups:
                    self.errors.append(f"[Warning] : Object layer '{layer_name}' is missing.")
            else:
                if layer_name not in layers:
                    self.errors.append(f"[Warning] : Layer '{layer_name}' is missing.")
                elif layers[layer_name].find('data').get('encoding') != 'csv':
                    self.errors.append(f"[ERROR] : Layer '{layer_name}' is not encoded in CSV.")
                else:
                    # Check size and count tiles
                    width = int(layers[layer_name].get('width'))
                    height = int(layers[layer_name].get('height'))
                    data_text = layers[layer_name].find('data').text
                    tile_count = len(data_text.strip().split(',')) if data_text else 0
                    layer_sizes.append((width, height))
                    tile_counts.append(tile_count)

        # Verify all non-object layers have the same size
        if len(set(layer_sizes)) > 1:
            self.errors.append("[ERROR] : Layer size inconsistency. Sizes found: " + str(set(layer_sizes)))

        # Verify all non-object layers have the same number of tiles
        if len(set(tile_counts)) > 1:
            self.errors.append("[ERROR] : Layer tile count inconsistency. Counts found: " + str(set(tile_counts)))

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 TmxValidator.py <path_to_tmx_file>")
        sys.exit(1)

    file_path = sys.argv[1]
    validator = TmxValidator(file_path)
    errors = validator.validate()

    if errors:
        for error in errors:
            print(error)
    else:
        print("TMX file is valid.")

if __name__ == "__main__":
    main()
