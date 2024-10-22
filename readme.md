# 2D Convolution Program

This project implements a 2D convolution operation on a large matrix using a filter kernel. It provides two versions of the convolution program, each demonstrating different approaches to storing and processing the filtered values. The project includes functionality to perform multiple iterations of convolution, scaling, and saturation of the output values.

## Features

- **2D Convolution**: Applies a filter kernel to a 1024x1024 matrix of input data.
- **Multiple Iterations**: Allows for repeated application of the convolution operation as specified by the user.
- **Scaling and Saturation**: Includes operations to scale and saturate the convolution results for a more controlled output.

## Usage

1. Compile the programs using `gcc`:

    ```bash
    gcc convolution1.c -o convolution1
    gcc convolution2.c -o convolution2
    ```

2. Run the programs with the following command structure:

    ```bash
    ./convolution1 <data_file> <filter_file> <output_file> <iterations>
    ./convolution2 <data_file> <filter_file> <output_file> <iterations>
    ```

    - `data_file`: Path to the input matrix file (1024x1024 integers).
    - `filter_file`: Path to the filter kernel file (5x5 integers).
    - `output_file`: Path where the final convolved matrix will be saved.
    - `iterations`: Number of convolution iterations to perform.

3. Example execution:

    ```bash
    time ./convolution1 data1.txt filter1.txt temp111 1 [UNIX]
    Measure-Command { ./convolution1 data1.txt filter1.txt temp111 1 } [WINDOWS]
    ```

    This command runs `convolution1` with a single iteration using `data1.txt` and `filter1.txt`, storing the output in `temp111`.

4. Compare the output with a reference output file to verify correctness:

    ```bash
    diff temp111 sample/temp111 [UNIX]
    Compare-Object (Get-Content temp111) (Get-Content sample\temp111) [WINDOWS]

    ```

    This command checks for differences between the generated output and a sample output file.

## Files

- `convolution1.c`: Implements convolution with a struct-based approach to store original and new values.
- `convolution2.c`: Implements convolution using arrays to store the results.
- `data1.txt`: Sample input matrix file.
- `filterX.txt`: Sample filter X kernel file.
- `sample/temp111`: Sample output file for verification.

## Requirements

- `gcc` for compilation.
- Standard C libraries (`stdio.h`, `stdlib.h`, etc.).
- Basic knowledge of matrix operations and file handling in C.

## Performance Testing

To measure the execution time, use the `time` command as shown in the example above. This will help evaluate the performance impact of different iteration counts or matrix sizes.