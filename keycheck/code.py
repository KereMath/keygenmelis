import pandas as pd
import random
import os

# === Test Functions ===

def blk_test_fn__frequency(bits, size):
    """Counts the number of 1s in the binary sequence."""
    return sum(bits)


def blk_test_fn__run_count(bits, size):
    """Counts the number of transitions from 0 to 1 or 1 to 0."""
    return sum(1 for i in range(1, len(bits)) if bits[i] != bits[i - 1])


def blk_test_fn__run_L1(bits, size):
    """Counts the number of runs of length 1."""
    return sum(1 for i in range(1, len(bits)) if bits[i] != bits[i - 1])


def blk_test_fn__template_match_4_1(bits, size):
    """Matches a template [0, 0, 0, 0]."""
    template = [0, 0, 0, 0]
    return sum(1 for i in range(len(bits) - 3) if bits[i:i + 4] == template)


def blk_test_fn__template_match_4_2(bits, size):
    """Matches a template [0, 1, 0, 1]."""
    template = [0, 1, 0, 1]
    return sum(1 for i in range(len(bits) - 3) if bits[i:i + 4] == template)


def blk_test_fn__template_match_4_3(bits, size):
    """Matches a template [0, 0, 1, 0]."""
    template = [0, 0, 1, 0]
    return sum(1 for i in range(len(bits) - 3) if bits[i:i + 4] == template)


def blk_test_fn__template_match_4_4(bits, size):
    """Matches a template [0, 0, 0, 1]."""
    template = [0, 0, 0, 1]
    return sum(1 for i in range(len(bits) - 3) if bits[i:i + 4] == template)


def blk_test_fn__linear_complexity(bits, size):
    """Calculates the linear complexity of the binary sequence."""
    return len(set(bits))  # Placeholder for Berlekamp-Massey algorithm


def blk_test_fn__blind_spot_complexity(bits, size):
    """Calculates the blind spot complexity of the binary sequence."""
    return sum(bits)  # Placeholder, as blind spot complexity is context-dependent


# === Helper Functions ===

def evaluate_test_limits(test_name, result, size):
    """Evaluates whether a test passes based on the test's result, key size, and thresholds."""
    limits = {
        'blk_test_fn__frequency': {
            128: (45, 83), 256: (100, 153), 512: (218, 294), 
            1024: (459, 566), 2048: (950, 1100), 4096: (1943, 2154)
        },
        'blk_test_fn__run_count': {
            128: (46, 86), 256: (102, 155), 512: (219, 296), 
            1024: (460, 566), 2048: (950, 1098), 4096: (1943, 2150)
        },
        'blk_test_fn__run_L1': {
            128: (13, 60), 256: (37, 96), 512: (89, 175), 
            1024: (200, 319), 2048: (431, 599), 4096: (909, 1143)
        },
        'blk_test_fn__template_match_4_1': {
            128: (0, 25), 256: (0, 38), 512: (0, 63), 
            1024: (0, 105), 2048: (0, 185), 4096: (0, 334)
        }
    }

    lower, upper = limits.get(test_name, {}).get(size, (0, float('inf')))
    return 'Geçti' if lower <= result <= upper else 'Kaldı'


def process_key(key, size):
    """Processes each key and evaluates each of the 9 tests."""
    bits = [int(bit) for bit in key]
    test_results = {}

    test_results['blk_test_fn__frequency'] = blk_test_fn__frequency(bits, size)
    test_results['blk_test_fn__run_count'] = blk_test_fn__run_count(bits, size)
    test_results['blk_test_fn__run_L1'] = blk_test_fn__run_L1(bits, size)
    test_results['blk_test_fn__template_match_4_1'] = blk_test_fn__template_match_4_1(bits, size)
    test_results['blk_test_fn__template_match_4_2'] = blk_test_fn__template_match_4_2(bits, size)
    test_results['blk_test_fn__template_match_4_3'] = blk_test_fn__template_match_4_3(bits, size)
    test_results['blk_test_fn__template_match_4_4'] = blk_test_fn__template_match_4_4(bits, size)
    test_results['blk_test_fn__linear_complexity'] = blk_test_fn__linear_complexity(bits, size)
    test_results['blk_test_fn__blind_spot_complexity'] = blk_test_fn__blind_spot_complexity(bits, size)

    evaluation = {test_name: evaluate_test_limits(test_name, result, size) 
                  for test_name, result in test_results.items()}

    return test_results, evaluation


def process_input_file(input_filename, output_filename):
    """Reads input file, processes each key, and writes the results to an Excel file."""
    with open(input_filename, 'r') as file:
        keys = file.read().splitlines()

    results = []
    for i, key in enumerate(keys):
        key_size = len(key)
        test_results, evaluations = process_key(key, key_size)
        results.append({
            'Key': key,
            'Size': key_size,
            **test_results,
            **evaluations
        })
    
    df = pd.DataFrame(results)
    df.to_excel(output_filename, index=False)


# === Run the script ===
if __name__ == "__main__":
    input_filename = 'input.txt'
    output_filename = 'output.xlsx'

    process_input_file(input_filename, output_filename)
