{ rustPlatform }:

rustPlatform.buildRustPackage rec {
  name = "ASCIIVN-${version}";
  version = "0.1.0";

  src = ./.;
  cargoSha256 = "0sjjj9z1dhilhpc8pq4154czrb79z9cm044jvn75kxcjv6v5l2m5";
}
