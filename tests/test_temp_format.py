def format_celsius(c_str):
    # Remove quotes if present (JSON.stringify adds them)
    c_str = c_str.strip('"')
    try:
        val = float(c_str)
        # Format to 2 decimal places, no extra spaces
        return f"{val:.2f}C"
    except ValueError:
        return "N/A"

def celsius_to_fahrenheit(c_str):
    c_str = c_str.strip('"')
    try:
        val = float(c_str)
        f_val = (val * 9/5) + 32
        return f"{f_val:.1f}F"
    except ValueError:
        return "N/A"

def test_formatting():
    test_cases = [
        ("2.34", "2.34C"),
        ("10.5", "10.50C"),
        ("0", "0.00C"),
        ("-5.1", "-5.10C")
    ]
    for inp, expected in test_cases:
        result = format_celsius(inp)
        assert result == expected, f"Expected {expected}, got {result}"
        print(f"Pass: {inp} -> {result}")

def test_conversion():
    test_cases = [
        ("0", "32.0F"),
        ("100", "212.0F"),
        ("-40", "-40.0F"),
        ("20", "68.0F")
    ]
    for inp, expected in test_cases:
        result = celsius_to_fahrenheit(inp)
        assert result == expected, f"Expected {expected}, got {result}"
        print(f"Pass: {inp} -> {result}")

if __name__ == "__main__":
    test_formatting()
    test_conversion()
