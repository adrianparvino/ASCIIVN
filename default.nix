{ pkgs ? (import <nixpkgs> {})
, stdenv ? pkgs.stdenv
, cmake ? pkgs.cmake
, libpng ? pkgs.libpng
}:

stdenv.mkDerivation rec {
  name = "TamagoC";
  version = "0.0.1";

  src = ./.;

  buildInputs =
    [ cmake libpng ];
}
