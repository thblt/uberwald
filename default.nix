with import <nixpkgs>{};

{ nixpkgs ? import <nixpkgs> {} }:
stdenv.mkDerivation {
  name = "uberwald-0.0.0";
  src = fetchgit {
    url = "https://github.com/thblt/uberwald";
    sha256 = "1wy645v6cy9pns4gxqb6vb939fd2smp8hhzfsdv43c5yipn1nqmf";
  };

  buildInputs = with pkgs; [readline];
}
