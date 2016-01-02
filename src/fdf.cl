
__kernel void compute_matrix(const float scale,
							__global const float *matrix,
							__global const float *coordinates_x,
							__global const float *coordinates_y,
							__global const float *coordinates_z,
							__global float *result)
{
	int gid = get_global_id(0);
	result[gid] = coordinates_x[gid] * matrix[0] + coordinates_y[gid] * matrix[1] + coordinates_z[gid] * matrix[2] + matrix[3];
	result[gid] = result[gid] * scale;
}

__kernel void rasterize(__global float *x,
                       __global float *z,
                       float depth,
                       int shift,
                       float scale,
                       float window,
                       __global int *result)
{
    int gid = get_global_id(0);
    result[gid] = (int)(((x[gid] / (z[gid] + depth)) * (float)shift) * scale + window / 2.0);
}
