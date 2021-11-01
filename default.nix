with import <nixpkgs> {};

{ nixpkgs ? import <nixpkgs> {} }:

  stdenv.mkDerivation rec {
  version = "0.0.0";
  name = "uberwald-${version}";

  # src = fetchgit {
  #   url = "https://github.com/thblt/uberwald";
  #   sha256 = "1wy645v6cy9pns4gxqb6vb939fd2smp8hhzfsdv43c5yipn1nqmf";
  # };

  buildInputs = with pkgs; [
    cmake
    readline
    clang
    doxygen
    check
    bear
    ctags
    python38Packages.sphinx
    python38Packages.breathe
    python38Packages.sphinx_rtd_theme
    lldb ];
}
