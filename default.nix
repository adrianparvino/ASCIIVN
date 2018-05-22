{ pkgs ? (import <nixpkgs> {})
, stdenv ? pkgs.stdenv
, cmake ? pkgs.cmake
, libpng ? pkgs.libpng
}:

let asciivn = stdenv.mkDerivation rec {
  name = "ASCIIVN";
  version = "0.0.1";

  src = ./.;

  buildInputs =
    [ cmake libpng ];
}; in
pkgs.writeScriptBin "run-asciivn" ''
  #!${pkgs.stdenv.shell}

  cd ${asciivn}/bin
  exec ./asciivn $@
''
