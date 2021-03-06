# ITLab Vision Group

[![Build Status](https://travis-ci.org/UNN-VMK-Software/itlab-vision.png?branch=master)](https://travis-ci.org/UNN-VMK-Software/itlab-vision)
[![Coverage Status](https://coveralls.io/repos/UNN-VMK-Software/itlab-vision/badge.png)](https://coveralls.io/r/UNN-VMK-Software/itlab-vision)
[![Documentation](https://readthedocs.org/projects/itlab-vision/badge/?version=latest)](http://itlab-vision.readthedocs.org)

This project is developed at Nizhny Novgorod State University (CMC faculty,
ITLab laboratory) and supported by the [Itseez](http://itseez.com) company.

Project maintainers:

  - [Valentina Kustikova](https://github.com/valentina-kustikova)
  - [Pavel Druzhkov](https://github.com/druzhkov-paul)
  - [Kirill Kornyakov](https://github.com/kirill-kornyakov)

Project developers:
  - [Evgeniy Dolotov](https://github.com/DolotovEvgeniy)
  - [Artem Screbkov](https://github.com/stragger)
  - [Dmitriy Kruchinin](https://github.com/KruchDmitriy)
  - [Vadim Levin](https://github.com/VadimLevin)
  - [Vlad Vinogradov](https://github.com/VladVin)

## Build and Run instructions

Build:

```
    $ mkdir photofilters
    $ cd photofilters
    $ git clone https://github.com/UNN-VMK-Software/itlab-vision.git
    $ mkdir build
    $ cd build
    $ cmake ../itlab-vision/photoeffects/
    $ make
    $ cd ./bin
```

Tests execution:

```
    $ ./photoeffects_test
```

Samples execution:

```
    $ ./antique_sample testdata/antique_test.png testdata/antique_texture_test.png 0.7
    $ ./edgeBlur_sample testdata/edgeBlur_test.png
    $ ./filmGrain_sample testdata/filmGrain_test.png 7
    $ ./matte_sample testdata/matte_test.png 25 25
    $ ./vignette_sample testdata/antique_test.png
    $ ./boostColor_sample testdata/boostColor_test.png 0.2
    $ ./fadeColor_sample testdata/fadeColor_test.png
    $ ./glow_sample testdata/glow_test.png 25 0.8
    $ ./sepia_sample testdata/antique_test.png
    $ ./tint_sample testdata/antique_test.png
    $ ./warmify_sample testdata/antique_test.png
```
