use dim::Dim;
use buffer::buffer2d::Buffer2d;
use buffer::block_iterator::BlockIterator;
use buffer::block_iterator::IntoBlockIterator;

pub struct Imagebuffer {
    pub background: u32,
    pub color_type: u32,
    pub pixel_size: u8,

    pub buffer: Buffer2d<u8>
}

impl IntoBlockIterator for Imagebuffer {
    type BlockIter = BlockIterator<Imagebuffer>;

    fn into_iter(self, dim: Dim) -> Self::BlockIter
    {
        BlockIterator {
            stride: dim,
            location: Dim { height: 0, width: 0 },

            buffer: self
        }
    }

    fn from_iter(blockiter: Self::BlockIter) -> Imagebuffer
    {
        blockiter.buffer
    }
}

impl Iterator for BlockIterator<Imagebuffer> {
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
