use dim::Dim;
use buffer::buffer2d::Buffer2d;
use buffer::block_iterator::BlockIterator;

pub struct Imagebuffer {
    pub background: u32,
    pub color_type: u32,
    pub pixel_size: u8,

    pub buffer: Buffer2d<u8>
}

fn into_iter(imagebuffer: Imagebuffer,
             dim: Dim) -> BlockIterator<Imagebuffer>
{
    BlockIterator {
        stride: dim,
        location: Dim { height: 0, width: 0 },

        buffer: imagebuffer
    }
}

fn from_iter(blockiter: BlockIterator<Imagebuffer>) -> Imagebuffer
{
    blockiter.buffer
}
