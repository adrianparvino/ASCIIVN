use dim::Dim;

pub struct Imagebuffer {
    pub dim: Dim,

    pub background: u32,
    pub color_type: u32,
    pub pixel_size: u8,

    pub buffer: Vec<u8>
}

fn into_iter(imagebuffer: ImageBuffer,
             dim: Dim) -> Iterator
{
}

fn from_iter(imagebuffer: Iterator,
             dim: Dim) -> ImageBuffer
{
}
