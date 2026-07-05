__kernel void addMatrix(
    __global const float* A,
    __global const float* B,
    __global float* res,
    const int row,
    const int col)
{
    int x = get_global_id(0);
    int y = get_global_id(1);
    if (x < col && y < row) {
        int idx = y * col + x;
        res[idx] = A[idx] + B[idx];
    }
}


__kernel void addVector(
    __global const float* A,
    __global const float* B,
    __global float* C,
    const int n)
{
    int i = get_global_id(0);
    if (i < n)
        C[i] = A[i] + B[i];
}


__kernel void subtractMatrix(
    __global const float* A,
    __global const float* B,
    __global float* res,
    const int row,
    const int col)
{
    int x = get_global_id(0);
    int y = get_global_id(1);
    if (x < col && y < row) {
        int idx = y * col + x;
        res[idx] = A[idx] - B[idx];
    }
}


__kernel void subtractVector(
    __global const float* A,
    __global const float* B,
    __global float* C,
    const int n)
{
    int i = get_global_id(0);
    if (i < n)
        C[i] = A[i] - B[i];
}


__kernel void multiplyMatrix(
    __global const float* A,
    const int rowA,
    const int colA,
    __global const float* B,
    const int rowB,
    const int colB,
    __global float* res)
{
    int x = get_global_id(0);
    int y = get_global_id(1);
    
    if (x < colB && y < rowA) {
        float sum = 0.0f;
        for (int k = 0; k < colA; k++) {
            sum += A[y * colA + k] * B[k * colB + x];
        }
        res[y * colB + x] = sum;
    }
}
