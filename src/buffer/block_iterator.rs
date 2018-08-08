use dim::Dim;
use buffer::asciibuffer::Asciibuffer;
use buffer::imagebuffer::Imagebuffer;
use buffer::buffer2d::Buffer2d;

pub struct BlockIterator<T> {
    pub stride: Dim,
    pub location: Dim,

    pub buffer: T
}

pub trait IntoBlockIterator {
    type BlockIter;

    fn into_iter(self,
                 dim: Dim) -> Self::BlockIter;
    fn from_iter(blockiter: Self::BlockIter) -> Self;

}
