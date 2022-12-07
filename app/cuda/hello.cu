#include <hello.cuh>

__global__ void cuda_hello()
{
	printf("Hello World du GPU\n");
}

void kernel()
{
	printf("Hello World du CPU\n");

	// Launch CUDA kernel.
	cuda_hello<<<1, 1>>>();

	cudaDeviceSynchronize();
}