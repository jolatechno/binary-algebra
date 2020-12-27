#ifdef MPIENABLED
  /*
  set pool size
  */


  void Matrix::set_pool_size(int _num_workers) {
    num_workers = _num_workers;
  }

  void Vector::set_pool_size(int _num_workers) {
    num_workers = _num_workers;
  }


  /*
  simple send and receive
  */


  int Matrix::send(int to) const {
    return this->send(to, 0, 0, height, width);
  }

  int Vector::send(int to) const {
    return this->send(to, 0, height);
  }

  int Matrix::receive(int from) {
    return this->receive(from, 0, 0, height, width);
  }

  int Vector::receive(int from) {
    return this->receive(from, 0, height);
  }


  /*
  more complex send and receive
  */


  int Matrix::send(int to, int start_i, int start_j, int length_i, int length_j) const {
    int size[2] = {height, width};
    int start[2] = {start_i, start_j};
    int length[2] = {length_i, length_j};
    return mpi::send(to, size, start, length, blocks);
  }

  int Vector::send(int to, int start, int length) const {
    return mpi::send(to, start, length, blocks);
  }

  int Matrix::receive(int from, int start_i, int start_j, int length_i, int length_j) {
    int size[2] = {height, width};
    int start[2] = {start_i, start_j};
    int length[2] = {length_i, length_j};
    return mpi::receive(from, size, start, length, blocks);
  }

  int Vector::receive(int from, int start, int length) {
    return mpi::receive(from, start, length, blocks);
  }
#endif
