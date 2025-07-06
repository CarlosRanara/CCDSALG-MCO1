#!/usr/bin/env python3
"""
Input File Generator for Graham's Scan Project
Generates input2^6.txt through input2^15.txt with required point counts
CCDSALG Term 3, AY 2024-2025
"""

import math
import random

def generate_circular_points(n, radius, center_x=0, center_y=0):
    """Generate points on a circle with some interior points"""
    points = []
    
    # Generate points on the circle (about 70% of total)
    circle_points = int(n * 0.7)
    for i in range(circle_points):
        angle = 2 * math.pi * i / circle_points
        x = center_x + radius * math.cos(angle)
        y = center_y + radius * math.sin(angle)
        # Add small random noise
        x += random.uniform(-0.1, 0.1)
        y += random.uniform(-0.1, 0.1)
        points.append((x, y))
    
    # Generate interior points (about 30% of total)
    interior_points = n - circle_points
    for i in range(interior_points):
        # Random points inside the circle
        r = random.uniform(0, radius * 0.8)
        angle = random.uniform(0, 2 * math.pi)
        x = center_x + r * math.cos(angle)
        y = center_y + r * math.sin(angle)
        points.append((x, y))
    
    return points

def generate_mixed_pattern(n, scale):
    """Generate a mix of circular, linear, and random points"""
    points = []
    
    # Outer boundary (circle)
    boundary_points = min(n // 4, 100)
    for i in range(boundary_points):
        angle = 2 * math.pi * i / boundary_points
        x = scale * math.cos(angle)
        y = scale * math.sin(angle)
        points.append((x, y))
    
    # Some linear arrangements
    linear_points = min(n // 6, 50)
    for i in range(linear_points):
        # Horizontal line
        x = -scale + (2 * scale * i / linear_points)
        y = 0
        points.append((x, y))
        
        # Vertical line
        x = 0
        y = -scale + (2 * scale * i / linear_points)
        points.append((x, y))
    
    # Random interior points
    remaining = n - len(points)
    for i in range(remaining):
        x = random.uniform(-scale * 0.9, scale * 0.9)
        y = random.uniform(-scale * 0.9, scale * 0.9)
        points.append((x, y))
    
    return points[:n]  # Ensure exactly n points

def write_input_file(filename, points):
    """Write points to input file in required format"""
    with open(filename, 'w') as f:
        f.write(f"{len(points)}\n")
        for x, y in points:
            f.write(f"{x:10.6f} {y:10.6f}\n")

def main():
    """Generate all input files"""
    # Set random seed for reproducible results
    random.seed(42)
    
    test_cases = [
        (6, 64),      # 2^6
        (7, 128),     # 2^7
        (8, 256),     # 2^8
        (9, 512),     # 2^9
        (10, 1024),   # 2^10
        (11, 2048),   # 2^11
        (12, 4096),   # 2^12
        (13, 8192),   # 2^13
        (14, 16384),  # 2^14
        (15, 32768)   # 2^15
    ]
    
    for exponent, n in test_cases:
        filename = f"input2^{exponent}.txt"
        print(f"Generating {filename} with {n} points...")
        
        # Scale the coordinates based on number of points
        scale = 10 + (exponent * 2)  # Larger scale for larger datasets
        
        if exponent <= 8:
            # Smaller test cases - use circular pattern
            points = generate_circular_points(n, scale)
        else:
            # Larger test cases - use mixed pattern
            points = generate_mixed_pattern(n, scale)
        
        write_input_file(filename, points)
        print(f"✓ {filename} created with {len(points)} points")
    
    print("\nAll input files generated successfully!")
    print("\nTest your programs with:")
    print("./graham_slow")
    print("./graham_fast")

if __name__ == "__main__":
    main()
