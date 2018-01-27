/*
17.5.1.3 The Meaning of Copy
*/

struct Representation
{
  // huge...
};

struct Descriptor
{

};

class Image
{
public:
  // ...
  Image();
  Image(const Image& a); // copy constructor
  ~Image();
  // ...
  void write_block(Descriptor);
  // ...
private:
  Representation* clone(); // copy *rep
  Representation* rep;
  bool shared;
};

Image::Image()
  : rep{ new Representation{} },
  shared{ false }
{}

// do shallow copy and prepare for copy-on-write
Image::Image(const Image& a)
  : rep{ a.rep },
  shared{ true }
{}

Image::~Image()
{
  if (!shared)
    delete rep;
}

void Image::write_block(Descriptor d)
{
  if (shared)
  {
    rep = clone(); // make a copy of *rep
    shared = false; // no more sharing
  }
  // ...now we can safely write to our own copy of rep...
}

Representation* Image::clone()
{
  return new Representation{ *rep };
}

int main()
{
  Image i1;
  Image i2{ i1 };
  // ...
  Descriptor d;
  i2.write_block(d);
  // no more sharing
}