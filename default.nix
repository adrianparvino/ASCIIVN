{ pkgs ? (import <nixpkgs> {})
, stdenv ? pkgs.stdenv
, cmake ? pkgs.cmake
, aalib ? pkgs.aalib
}:

stdenv.mkDerivation rec {
  name = "TamagoC";
  version = "0.0.1";

  src = ./.;

  buildInputs =
    [ cmake aalib.dev ];
}
