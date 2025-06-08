import csv

# Configurable paths
csv_file = r"..\data\event_data.csv"
output_file = r"..\src\Gromit\EventSystem\EventType.h"

# Read CSV and extract the "Enum" column (skip header)
event_names = []
with open(csv_file, newline='') as file:
    reader = csv.DictReader(file)
    for row in reader:
        enum_name = row["Enum"].strip()
        if enum_name:
            event_names.append(enum_name)

# Generate C++ enum class
with open(output_file, "w") as f:
    f.write("#pragma once\n\n")
    f.write("enum class EventType {\n")
    for i, name in enumerate(event_names):
        comma = "," if i < len(event_names) - 1 else ""
        f.write(f"    {name}{comma}\n")
    f.write("};\n")

print(f"Enum class written to {output_file}")