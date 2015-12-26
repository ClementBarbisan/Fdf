
__kernel void compute_matrix(__global const float zoom,
							__global const float *matrix,
							__global const float *coordinates_x,
							__global const float *coordinates_y,
							__global const float *coordinates_z,
							__global float *result)
{
	int gid = get_global_id(0);
	result[gid] = coordinates_x[gid] * matrix[0] + coordinates_y[gid] * matrix[1] + coordinates_z[gid] * matrix[2] + matrix[3];
	result[gid] = result[gid] * zoom;
}
