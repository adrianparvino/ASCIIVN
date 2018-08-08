use dim::Dim;
use buffer::asciibuffer::Asciibuffer;
use buffer::imagebuffer::Imagebuffer;
use buffer::buffer2d::Buffer2d;

pub struct BlockIterator<T> {
    pub stride: Dim,
    pub location: Dim,

    pub buffer: T
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
