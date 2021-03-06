# Centreon Clib #

Centreon Clib is an open-source utility library used by some Centreon
software. It is a low-level component of the
[Centreon software suite](https://www.centreon.com).

Centreon Clib is released under the Apache Software License version 2
and is endorsed by the [Centreon company](https://www.centreon.com).

## Documentation ##

The full Centreon Clib documentation is available online
[here](https://documentation.centreon.com/docs/centreon-clib/en/latest/).
It is generated from ReST files located in the *./doc/* directory of
Centreon Clib sources.

The documentation extensively covers all aspects of Centreon Clib such
as installation, compilation, configuration, use and more. It is the
reference guide of the software. This *README* is only provided as a
quick introduction.

## Installing from binaries ##

**Warning**: Centreon Clib is a low-level component of the Centreon
software suite. If this is your first installation you would probably
want to [install it entirely](https://documentation.centreon.com/docs/centreon/en/2.6.x/installation/index.html).

Centreon ([the company behind the Centreon software suite](http://www.centreon.com))
provides binary packages for RedHat / CentOS. They are available either
as part of the [Centreon Entreprise Server distribution](https://www.centreon.com/en/products/centreon-enterprise-server/)
or as individual packages on [our RPM repository](https://documentation.centreon.com/docs/centreon/en/2.6.x/installation/from_packages.html).

Once the repository installed a simple command will be needed to install
Centreon Clib.

    $# yum install centreon-clib

## Fetching sources ##

The reference repository is hosted at [GitHub](https://github.com/centreon/centreon-clib).
Beware that the repository hosts in-development sources and that it
might not work at all.

Stable releases are available as gziped tarballs on [Centreon's download site](https://download.centreon.com).

## Compilation (quickstart) ##

**Warning**: Centreon Clib is a low-level component of the Centreon
software suite. If this is your first installation you would probably
want to [install it entirely](https://documentation.centreon.com/docs/centreon/en/2.6.x/installation/index.html).

This paragraph is only a quickstart guide for the compilation of
Centreon Clib. For a more in-depth guide with build options you should
refer to the [online documentation](https://documentation.centreon.com/docs/centreon-clib/en/latest/).

Once the sources of Centreon Clib extracted, got to the *./build/*
directory and launch the CMake command. This will look for required
dependencies and print a summary of the compilation parameters if
everything went fine.

    $> cd centreon-clib/build
    $> cmake .
    ...

Now launch the compilation using the *make* command and then install the
software by running *make install* as priviledged user.

    $> make -j 4
    ...
    $# make install

You're done !

## Bug reports / Feature requests ##

The best way to report a bug or to request a feature is to open an issue
in GitHub's [issue tracker](https://github.com/centreon/centreon-clib/issues/).

Please note that Centreon Clib follows the
[same workflow as Centreon](https://github.com/centreon/centreon/blob/master/project/issues.md)
to process issues.

For a quick resolution of a bug your message should contain :

* the problem description
* precise steps on how to reproduce the issue (if you're using Centreon
  web UI tell us where you click)
* the expected behavior
* the Centreon product**s** version**s**
* the operating system you're using (name and version)
* if possible configuration, log and debug files

## Contributing ##

Contributions are much welcome ! If possible provide them as
pull-requests on GitHub. If not, patches will do but describe against
which version/commit they apply.

For any question or remark feel free to send a mail to the project
maintainer : Matthieu Kermagoret (mkermagoret@centreon.com).
