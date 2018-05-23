use dim::Dim;
use buffer::buffer2d::Buffer2d;

pub struct Imagebuffer {
    pub background: u32,
    pub color_type: u32,
    pub pixel_size: u8,

    pub buffer: Buffer2d<u8> }

fn into_iter(imagebuffer: Imagebuffer,
                 dim: Dim) -> BlockIterator
{
    BlockIterator {
        stride: dim,
        location: Dim { height: 0, width: 0 },

        buffer: imagebuffer
    }
}

fn from_iter(blockiter: BlockIterator) -> Imagebuffer
{
    blockiter.buffer
}

struct BlockIterator {
    stride: Dim,
    location: Dim,

    buffer: Imagebuffer
}


impl Iterator for BlockIterator {
    type Item = Imagebuffer;

    fn next(&mut self) -> Option<Imagebuffer> {
        let x = self.location.width;
        let y = self.location.height;
        let w = self.stride.width;
        let h = self.stride.height;

        let ret = Imagebuffer {
            background: self.buffer.background,
            color_type: self.buffer.color_type,
            pixel_size: self.buffer.pixel_size,

            buffer: Buffer2d {
                dim: Dim { height: self.stride.height, width: self.stride.width },
                buffer: self.buffer.buffer.buffer[y..y+h]
                            .iter()
                            .map(|v| v[x..x+w].to_vec())
                            .collect()
            }
        };

        self.location.width += self.stride.width;

        Some(ret)
    }
}
