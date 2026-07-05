package ua.lvivpoly;

import org.jocl.*;

import java.io.InputStream;
import java.nio.charset.StandardCharsets;


public class AlgebraUtilsOCL {
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue commandQueue;
    cl_program program;

    public void initCL() {
        // Ініціалізація OpenCL
        CL.setExceptionsEnabled(true);
        cl_platform_id[] platforms = new cl_platform_id[1];
        CL.clGetPlatformIDs(platforms.length, platforms, null);
        platform = platforms[0];

        cl_device_id[] devices = new cl_device_id[1];
        CL.clGetDeviceIDs(platform, CL.CL_DEVICE_TYPE_ALL, devices.length, devices, null);
        device = devices[0];

        context = CL.clCreateContext(null, 1, new cl_device_id[]{device}, null, null, null);
        commandQueue = CL.clCreateCommandQueue(context, device, 0, null);

        // Читаємо kernel з resources
        String source = "";
        try (InputStream stream = AlgebraUtilsOCL.class.getResourceAsStream("/ua/lvivpoly/AlgebraUtils.cl")) {
            source = new String(stream.readAllBytes(), StandardCharsets.UTF_8);
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }

        program = CL.clCreateProgramWithSource(context, 1, new String[]{source}, null, null);

        int[] err = new int[1];
        err[0] = CL.clBuildProgram(program, 0, null, null, null, null);
        if (err[0] != CL.CL_SUCCESS) {
            long[] logSize = new long[1];
            CL.clGetProgramBuildInfo(program, device, CL.CL_PROGRAM_BUILD_LOG, 0, null, logSize);
            byte[] logData = new byte[(int) logSize[0]];
            CL.clGetProgramBuildInfo(program, device, CL.CL_PROGRAM_BUILD_LOG, logSize[0], Pointer.to(logData), null);
            System.err.println("Build log:\n" + new String(logData, StandardCharsets.UTF_8));
        }
    }

    public void releaseCL() {
        CL.clReleaseProgram(program);
        CL.clReleaseCommandQueue(commandQueue);
        CL.clReleaseContext(context);
    }

    // adding
    public float[][] add(float[][] matrix1, float[][] matrix2) {
        int n = matrix1.length;
        if (n != matrix1[0].length || n != matrix2.length || n != matrix2[0].length) {
            throw new IllegalArgumentException("The matrix must be square and of the same size!");
        }

        // Create buffers
        cl_mem bufferA = CL.clCreateBuffer(context, CL.CL_MEM_READ_ONLY | CL.CL_MEM_COPY_HOST_PTR,
                Sizeof.cl_float * n * n, Pointer.to(flattenMatrix(matrix1)), null);
        cl_mem bufferB = CL.clCreateBuffer(context, CL.CL_MEM_READ_ONLY | CL.CL_MEM_COPY_HOST_PTR,
                Sizeof.cl_float * n * n, Pointer.to(flattenMatrix(matrix2)), null);
        cl_mem bufferC = CL.clCreateBuffer(context, CL.CL_MEM_WRITE_ONLY,
                Sizeof.cl_float * n * n, null, null);

        // Create kernel
        cl_kernel kernel = CL.clCreateKernel(program, "addMatrix", null);

        // Set kernel arguments
        CL.clSetKernelArg(kernel, 0, Sizeof.cl_mem, Pointer.to(bufferA));
        CL.clSetKernelArg(kernel, 1, Sizeof.cl_mem, Pointer.to(bufferB));
        CL.clSetKernelArg(kernel, 2, Sizeof.cl_mem, Pointer.to(bufferC));
        CL.clSetKernelArg(kernel, 3, Sizeof.cl_int, Pointer.to(new int[]{n}));
        CL.clSetKernelArg(kernel, 4, Sizeof.cl_int, Pointer.to(new int[]{n}));

        // Execute kernel
        long globalWorkSize[] = new long[]{n, n};
        CL.clEnqueueNDRangeKernel(commandQueue, kernel, 2, null, globalWorkSize, null, 0, null, null);

        // Read result
        float[] flatResult = new float[n * n];
        CL.clEnqueueReadBuffer(commandQueue, bufferC, CL.CL_TRUE, 0,
                Sizeof.cl_float * n * n, Pointer.to(flatResult), 0, null, null);

        // Release resources
        CL.clReleaseKernel(kernel);
        CL.clReleaseMemObject(bufferA);
        CL.clReleaseMemObject(bufferB);
        CL.clReleaseMemObject(bufferC);

        // Reshape
        return reshapeMatrix(flatResult, n, n);
    }

    public float[] add(float[] vector1, float[] vector2) {
        int n = vector1.length;
        if (n != vector2.length) {
            throw new IllegalArgumentException("The vector size must be the same!");
        } 

        // Create buffers
        cl_mem bufferA = CL.clCreateBuffer(context, CL.CL_MEM_READ_ONLY | CL.CL_MEM_COPY_HOST_PTR,
                Sizeof.cl_float * n, Pointer.to(vector1), null);
        cl_mem bufferB = CL.clCreateBuffer(context, CL.CL_MEM_READ_ONLY | CL.CL_MEM_COPY_HOST_PTR,
                Sizeof.cl_float * n, Pointer.to(vector2), null);
        cl_mem bufferC = CL.clCreateBuffer(context, CL.CL_MEM_WRITE_ONLY,
                Sizeof.cl_float * n, null, null);

        // Create kernel
        cl_kernel kernel = CL.clCreateKernel(program, "addVector", null);

        // Set kernel arguments
        CL.clSetKernelArg(kernel, 0, Sizeof.cl_mem, Pointer.to(bufferA));
        CL.clSetKernelArg(kernel, 1, Sizeof.cl_mem, Pointer.to(bufferB));
        CL.clSetKernelArg(kernel, 2, Sizeof.cl_mem, Pointer.to(bufferC));
        CL.clSetKernelArg(kernel, 3, Sizeof.cl_int, Pointer.to(new int[]{n}));

        // Execute kernel
        long globalWorkSize[] = new long[]{n};
        CL.clEnqueueNDRangeKernel(commandQueue, kernel, 1, null, globalWorkSize, null, 0, null, null);

        // Read result
        float[] result = new float[n];
        CL.clEnqueueReadBuffer(commandQueue, bufferC, CL.CL_TRUE, 0,
                Sizeof.cl_float * n, Pointer.to(result), 0, null, null);

        // Release resources
        CL.clReleaseKernel(kernel);
        CL.clReleaseMemObject(bufferA);
        CL.clReleaseMemObject(bufferB);
        CL.clReleaseMemObject(bufferC);

        // Reshape
        return result;
    }

    // subtraction
    public float[][] subtraction(float[][] matrix1, float[][] matrix2) {
        int n = matrix1.length;
        if (n != matrix1[0].length || n != matrix2.length || n != matrix2[0].length) {
            throw new IllegalArgumentException("The matrix must be square and of the same size!");
        }

        // Create buffers
        cl_mem bufferA = CL.clCreateBuffer(context, CL.CL_MEM_READ_ONLY | CL.CL_MEM_COPY_HOST_PTR,
                Sizeof.cl_float * n * n, Pointer.to(flattenMatrix(matrix1)), null);
        cl_mem bufferB = CL.clCreateBuffer(context, CL.CL_MEM_READ_ONLY | CL.CL_MEM_COPY_HOST_PTR,
                Sizeof.cl_float * n * n, Pointer.to(flattenMatrix(matrix2)), null);
        cl_mem bufferC = CL.clCreateBuffer(context, CL.CL_MEM_WRITE_ONLY,
                Sizeof.cl_float * n * n, null, null);

        // Create kernel
        cl_kernel kernel = CL.clCreateKernel(program, "subtractMatrix", null);

        // Set kernel arguments
        CL.clSetKernelArg(kernel, 0, Sizeof.cl_mem, Pointer.to(bufferA));
        CL.clSetKernelArg(kernel, 1, Sizeof.cl_mem, Pointer.to(bufferB));
        CL.clSetKernelArg(kernel, 2, Sizeof.cl_mem, Pointer.to(bufferC));
        CL.clSetKernelArg(kernel, 3, Sizeof.cl_int, Pointer.to(new int[]{n}));
        CL.clSetKernelArg(kernel, 4, Sizeof.cl_int, Pointer.to(new int[]{n}));

        // Execute kernel
        long globalWorkSize[] = new long[]{n, n};
        CL.clEnqueueNDRangeKernel(commandQueue, kernel, 2, null, globalWorkSize, null, 0, null, null);

        // Read result
        float[] flatResult = new float[n * n];
        CL.clEnqueueReadBuffer(commandQueue, bufferC, CL.CL_TRUE, 0,
                Sizeof.cl_float * n * n, Pointer.to(flatResult), 0, null, null);

        // Release resources
        CL.clReleaseKernel(kernel);
        CL.clReleaseMemObject(bufferA);
        CL.clReleaseMemObject(bufferB);
        CL.clReleaseMemObject(bufferC);

        // Reshape
        return reshapeMatrix(flatResult, n, n);
    }

    public float[] subtraction(float[] vector1, float[] vector2) {
        int n = vector1.length;
        if (n != vector2.length) {
            throw new IllegalArgumentException("The vector size must be the same!");
        } 

        // Create buffers
        cl_mem bufferA = CL.clCreateBuffer(context, CL.CL_MEM_READ_ONLY | CL.CL_MEM_COPY_HOST_PTR,
                Sizeof.cl_float * n, Pointer.to(vector1), null);
        cl_mem bufferB = CL.clCreateBuffer(context, CL.CL_MEM_READ_ONLY | CL.CL_MEM_COPY_HOST_PTR,
                Sizeof.cl_float * n, Pointer.to(vector2), null);
        cl_mem bufferC = CL.clCreateBuffer(context, CL.CL_MEM_WRITE_ONLY,
                Sizeof.cl_float * n, null, null);

        // Create kernel
        cl_kernel kernel = CL.clCreateKernel(program, "subtractVector", null);

        // Set kernel arguments
        CL.clSetKernelArg(kernel, 0, Sizeof.cl_mem, Pointer.to(bufferA));
        CL.clSetKernelArg(kernel, 1, Sizeof.cl_mem, Pointer.to(bufferB));
        CL.clSetKernelArg(kernel, 2, Sizeof.cl_mem, Pointer.to(bufferC));
        CL.clSetKernelArg(kernel, 3, Sizeof.cl_int, Pointer.to(new int[]{n}));

        // Execute kernel
        long globalWorkSize[] = new long[]{n};
        CL.clEnqueueNDRangeKernel(commandQueue, kernel, 1, null, globalWorkSize, null, 0, null, null);

        // Read result
        float[] result = new float[n];
        CL.clEnqueueReadBuffer(commandQueue, bufferC, CL.CL_TRUE, 0,
                Sizeof.cl_float * n, Pointer.to(result), 0, null, null);

        // Release resources
        CL.clReleaseKernel(kernel);
        CL.clReleaseMemObject(bufferA);
        CL.clReleaseMemObject(bufferB);
        CL.clReleaseMemObject(bufferC);

        // Reshape
        return result;
    }

    // multiplying
    public float[][] multiply(float[][] matrix1, float[][] matrix2) {
        int n = matrix1.length;
        if (n != matrix1[0].length || n != matrix2.length || n != matrix2[0].length) {
            throw new IllegalArgumentException("The matrix must be square and of the same size!");
        }

        // Create buffers
        cl_mem bufferA = CL.clCreateBuffer(context, CL.CL_MEM_READ_ONLY | CL.CL_MEM_COPY_HOST_PTR,
                Sizeof.cl_float * n * n, Pointer.to(flattenMatrix(matrix1)), null);
        cl_mem bufferB = CL.clCreateBuffer(context, CL.CL_MEM_READ_ONLY | CL.CL_MEM_COPY_HOST_PTR,
                Sizeof.cl_float * n * n, Pointer.to(flattenMatrix(matrix2)), null);
        cl_mem bufferC = CL.clCreateBuffer(context, CL.CL_MEM_WRITE_ONLY,
                Sizeof.cl_float * n * n, null, null);

        // Create kernel
        cl_kernel kernel = CL.clCreateKernel(program, "multiplyMatrix", null);

        // Set kernel arguments
        CL.clSetKernelArg(kernel, 0, Sizeof.cl_mem, Pointer.to(bufferA));
        CL.clSetKernelArg(kernel, 1, Sizeof.cl_int, Pointer.to(new int[]{n}));
        CL.clSetKernelArg(kernel, 2, Sizeof.cl_int, Pointer.to(new int[]{n}));
        CL.clSetKernelArg(kernel, 3, Sizeof.cl_mem, Pointer.to(bufferB));
        CL.clSetKernelArg(kernel, 4, Sizeof.cl_int, Pointer.to(new int[]{n}));
        CL.clSetKernelArg(kernel, 5, Sizeof.cl_int, Pointer.to(new int[]{n}));
        CL.clSetKernelArg(kernel, 6, Sizeof.cl_mem, Pointer.to(bufferC));


        // Execute kernel
        long globalWorkSize[] = new long[]{n, n};
        CL.clEnqueueNDRangeKernel(commandQueue, kernel, 2, null, globalWorkSize, null, 0, null, null);

        // Read result
        float[] flatResult = new float[n * n];
        CL.clEnqueueReadBuffer(commandQueue, bufferC, CL.CL_TRUE, 0,
                Sizeof.cl_float * n * n, Pointer.to(flatResult), 0, null, null);

        // Release resources
        CL.clReleaseKernel(kernel);
        CL.clReleaseMemObject(bufferA);
        CL.clReleaseMemObject(bufferB);
        CL.clReleaseMemObject(bufferC);

        // Reshape
        return reshapeMatrix(flatResult, n, n);
    }

    public float[] multiply(float[][] matrix, float[] vector) {
        int n = matrix.length;
        if (n != matrix[0].length || n != vector.length) {
            throw new IllegalArgumentException("The matrix must be square and the vector size must match the matrix size!");
        }

        // Create buffers
        cl_mem bufferA = CL.clCreateBuffer(context, CL.CL_MEM_READ_ONLY | CL.CL_MEM_COPY_HOST_PTR,
                Sizeof.cl_float * n * n, Pointer.to(flattenMatrix(matrix)), null);
        cl_mem bufferB = CL.clCreateBuffer(context, CL.CL_MEM_READ_ONLY | CL.CL_MEM_COPY_HOST_PTR,
                Sizeof.cl_float * n, Pointer.to(vector), null);
        cl_mem bufferC = CL.clCreateBuffer(context, CL.CL_MEM_WRITE_ONLY,
                Sizeof.cl_float * n, null, null);

        // Create kernel
        cl_kernel kernel = CL.clCreateKernel(program, "multiplyMatrix", null);

        // Set kernel arguments
        CL.clSetKernelArg(kernel, 0, Sizeof.cl_mem, Pointer.to(bufferA));
        CL.clSetKernelArg(kernel, 1, Sizeof.cl_int, Pointer.to(new int[]{n}));
        CL.clSetKernelArg(kernel, 2, Sizeof.cl_int, Pointer.to(new int[]{n}));
        CL.clSetKernelArg(kernel, 3, Sizeof.cl_mem, Pointer.to(bufferB));
        CL.clSetKernelArg(kernel, 4, Sizeof.cl_int, Pointer.to(new int[]{n}));
        CL.clSetKernelArg(kernel, 5, Sizeof.cl_int, Pointer.to(new int[]{1}));
        CL.clSetKernelArg(kernel, 6, Sizeof.cl_mem, Pointer.to(bufferC));

        // Execute kernel
        long globalWorkSize[] = new long[]{n, 1};
        CL.clEnqueueNDRangeKernel(commandQueue, kernel, 2, null, globalWorkSize, null, 0, null, null);

        // Read result
        float[] result = new float[n];
        CL.clEnqueueReadBuffer(commandQueue, bufferC, CL.CL_TRUE, 0,
                Sizeof.cl_float * n, Pointer.to(result), 0, null, null);

        // Release resources
        CL.clReleaseKernel(kernel);
        CL.clReleaseMemObject(bufferA);
        CL.clReleaseMemObject(bufferB);
        CL.clReleaseMemObject(bufferC);

        // Reshape
        return result;
    }

    public float[] multiply(float[] vector, float[][] matrix) {
        int n = matrix.length;
        if (n != matrix[0].length || n != vector.length) {
            throw new IllegalArgumentException("The matrix must be square and the vector size must match the matrix size!");
        } 

        // Create buffers
        cl_mem bufferA = CL.clCreateBuffer(context, CL.CL_MEM_READ_ONLY | CL.CL_MEM_COPY_HOST_PTR,
                Sizeof.cl_float * n, Pointer.to(vector), null);
        cl_mem bufferB = CL.clCreateBuffer(context, CL.CL_MEM_READ_ONLY | CL.CL_MEM_COPY_HOST_PTR,
                Sizeof.cl_float * n * n, Pointer.to(flattenMatrix(matrix)), null);
        cl_mem bufferC = CL.clCreateBuffer(context, CL.CL_MEM_WRITE_ONLY,
                Sizeof.cl_float * n, null, null);

        // Create kernel
        cl_kernel kernel = CL.clCreateKernel(program, "multiplyMatrix", null);

        // Set kernel arguments
        CL.clSetKernelArg(kernel, 0, Sizeof.cl_mem, Pointer.to(bufferA));
        CL.clSetKernelArg(kernel, 1, Sizeof.cl_int, Pointer.to(new int[]{1}));
        CL.clSetKernelArg(kernel, 2, Sizeof.cl_int, Pointer.to(new int[]{n}));
        CL.clSetKernelArg(kernel, 3, Sizeof.cl_mem, Pointer.to(bufferB));
        CL.clSetKernelArg(kernel, 4, Sizeof.cl_int, Pointer.to(new int[]{n}));
        CL.clSetKernelArg(kernel, 5, Sizeof.cl_int, Pointer.to(new int[]{n}));
        CL.clSetKernelArg(kernel, 6, Sizeof.cl_mem, Pointer.to(bufferC));

        // Execute kernel
        long globalWorkSize[] = new long[]{1, n};
        CL.clEnqueueNDRangeKernel(commandQueue, kernel, 2, null, globalWorkSize, null, 0, null, null);

        // Read result
        float[] result = new float[n];
        CL.clEnqueueReadBuffer(commandQueue, bufferC, CL.CL_TRUE, 0,
                Sizeof.cl_float * n, Pointer.to(result), 0, null, null);

        // Release resources
        CL.clReleaseKernel(kernel);
        CL.clReleaseMemObject(bufferA);
        CL.clReleaseMemObject(bufferB);
        CL.clReleaseMemObject(bufferC);

        // Reshape
        return result;
    }

    public float multiply(float[] vector1, float[] vector2)  {
        int n = vector1.length;
        if (n != vector2.length) {
            throw new IllegalArgumentException("The vector size must be the same!");
        } 

        float result = 0;
        for (int i = 0; i < n; i++) {
            result += vector1[i] * vector2[i];
        } 

        return result;
    }

    public float[][] multiply(float[][] matrix, float c) {
        int n = matrix.length;
        float[][] result = new float[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = matrix[i][j] * c;
            }
        }
        return result;
    }

    public float[][] multiply(float c, float[][] matrix) {
        return multiply(matrix, c);
    }

    public float[] multiply(float[] vector, float c) {
        int n = vector.length;
        float[] result = new float[n];
        for (int i = 0; i < n; i++) {
            result[i] = vector[i] * c;
        }
        return result;
    }

    public float[] multiply(float c, float[] vector) {
        return multiply(vector, c);
    }

    // special
    public float[][] transpose(float[][] matrix) {
        int n = matrix.length;

        float[][] result = new float[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[j][i] = matrix[i][j];
            }
        }
        return result;
    };

    public void calcVectorb(float[] b) {
        for (int i = 1, n = b.length; i <= n; i++) {
            b[i-1] = 21.0f / (float) Math.pow(i, 4.0);
        }
    };

    public void calcMatrixC2(float[][] C2) {
        float determinator;
        for (int i = 1, n = C2.length; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                determinator = i*i-2.0f*j;
                if (determinator != 0) {
                    C2[i-1][j-1] = 21.0f/determinator;
                } else {
                    C2[i-1][j-1] = 0;
                }
            }
        }
    };

    // helper
    private float[] flattenMatrix(float[][] matrix) {
        int rows = matrix.length;
        int cols = matrix[0].length;
        float[] flat = new float[rows * cols];
        for (int i = 0; i < rows; i++) {
            System.arraycopy(matrix[i], 0, flat, i * cols, cols);
        }
        return flat;
    }  

    private float[][] reshapeMatrix(float[] flat, int rows, int cols) {
        float[][] matrix = new float[rows][cols];
        for (int i = 0; i < rows; i++) {
            System.arraycopy(flat, i * cols, matrix[i], 0, cols);
        }
        return matrix;
    }
}
