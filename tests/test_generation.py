import random

num_points = 7000000
filename = 'generated_data.txt'
step = 0.1  

def generate_y(x):
    return 2 * x**3 + 6 * x**2 + x + 1 

with open(filename, 'w') as f:
    f.write("3\n")
    x = 1.0 
    while x <= num_points:  
        y = generate_y(x)
        f.write(f"{x} {y}\n")
        x += step  

print(f"The data is generated and written to a file {filename}")
