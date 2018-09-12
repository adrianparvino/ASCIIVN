use num_iter::range_step;

use buffer::imagebuffer::Imagebuffer;
use buffer::buffer2d::Buffer2d;
use dim::Dim;

pub fn bilinear_scale <'a>(src: Imagebuffer,
                           dim: Dim) -> Option<Imagebuffer>
{
    if (src.buffer.dim.width  % dim.width  != 0) { return None; }
    if (src.buffer.dim.height % dim.height != 0) { return None; }

    let stride_x = src.buffer.dim.width / dim.width;
    let stride_y = src.buffer.dim.height / dim.height;

    let buffer = src.buffer.buffer;

    let new_buffer =
        buffer.chunks(stride_y).map(|chunk_rows|
             chunk_rows.chunks(stride_x).map(|chunk| {
                 let mut new_pixel = 0;

                 for row in chunk
                 {
                     for pixel in row
                     {
                         new_pixel += *pixel as u64;
                     }
                 }

                 (new_pixel / (stride_x * stride_y) as u64) as u8
             }).collect()
        ).collect();


    Some(Imagebuffer {
        background: src.background,
        color_type: src.color_type,
        pixel_size: src.pixel_size,

        buffer: Buffer2d {
            dim: dim,
            buffer: new_buffer
        }
    })
}
