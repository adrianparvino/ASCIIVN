use dim::Dim;

pub struct Buffer2d<T> {
    pub dim: Dim,

    pub buffer: Vec<Vec<T>>
}
