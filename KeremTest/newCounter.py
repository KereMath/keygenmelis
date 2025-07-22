import os
import pandas as pd
from collections import defaultdict

# Define the folder path and output file
folder_path = r"C:\Users\J.A.R.V.I.S\Desktop\testExcel"
output_file = os.path.join(folder_path, "Test_Summary.xlsx")

# Initialize the summary dictionary
summary = defaultdict(lambda: defaultdict(lambda: {"Passed": 0, "Failed": 0}))

# Process each file in the folder
for file_name in os.listdir(folder_path):
    if file_name.endswith(".xlsx") and "_" in file_name:
        # Extract bit size from file name
        bit_size = int(file_name.split("_")[0])
        
        # Load the Excel file
        file_path = os.path.join(folder_path, file_name)
        df = pd.read_excel(file_path)
        
        # Process each column (except the first column)
        for column in df.columns[1:]:
            passed_count = (df[column] == "Passed").sum()
            failed_count = (df[column] == "Failed").sum()
            
            # Update the summary
            summary[bit_size][column]["Passed"] += passed_count
            summary[bit_size][column]["Failed"] += failed_count

# Prepare the summary DataFrame
rows = []
for bit_size, tests in sorted(summary.items()):
    row = {"Bit Size": bit_size}
    for test, results in tests.items():
        row[f"{test} (Passed)"] = results["Passed"]
        row[f"{test} (Failed)"] = results["Failed"]
    rows.append(row)

summary_df = pd.DataFrame(rows)

# Save the summary to a new Excel file
summary_df.to_excel(output_file, index=False)

print(f"Summary file saved to: {output_file}")
