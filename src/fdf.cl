
__kernel void compute_matrix(const float scale,
							__global const float *matrix,
							__global const float *coordinates_x,
							__global const float *coordinates_y,
							__global const float *coordinates_z,
							__global float *result)
{
	int gid1 = get_global_id(0);
	int gid2 = get_global_id(1);
	int gid3 = get_global_id(2);
	int size1 = get_global_size(0);
	int size2 = get_global_size(1);
	int index = gid1 + gid2 * size1 + gid3 * size1 * size2;
	result[index] = coordinates_x[index] * matrix[0] + coordinates_y[index] * matrix[1] + coordinates_z[index] * matrix[2] + matrix[3];
	result[index] = result[index] * scale;
}

__kernel void rasterize(__global float *x,
                       __global float *z,
                       float depth,
                       int shift,
                       float scale,
                       float window,
                       __global int *result)
{
	int gid1 = get_global_id(0);
	int gid2 = get_global_id(1);
	int gid3 = get_global_id(2);
	int size1 = get_global_size(0);
	int size2 = get_global_size(1);
	int index = gid1 + gid2 * size1 + gid3 * size1 * size2;
    result[index] = (int)(((x[index] / (z[index] + depth)) * (float)shift) * scale + window / 2.0);
}
