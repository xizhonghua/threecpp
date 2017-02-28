#!/bin/bash

cd ../

HEADER=three/renderers/shaders/ShaderChunk.h
SOURCE=three/renderers/shaders/ShaderChunk.cpp

#######################################################################
echo "// Generated file! Do NOT modify!" > $HEADER
echo >> $HEADER

echo "#ifndef THREE_RENDERERS_SHADERS_SHADERCHUNK_H_" >> $HEADER
echo "#define THREE_RENDERERS_SHADERS_SHADERCHUNK_H_" >> $HEADER
echo >> $HEADER

echo "namespace three {" >> $HEADER

echo "class ShaderChunk {" >> $HEADER
echo "public:" >> $HEADER


#######################################################################
echo "// Generated file! Do NOT modify!" > $SOURCE
echo >> $SOURCE

echo "#include <three/renderers/shaders/ShaderChunk.h>" >> $SOURCE
echo >> $SOURCE

echo "namespace three {" >> $SOURCE

for f in three/renderers/shaders/ShaderChunk/*.glsl three/renderers/shaders/ShaderLib/*.glsl; do

  filename=$(basename "$f")
  extension="${filename##*.}"
  filename="${filename%.*}"

  echo >> $HEADER
  echo "  static const char* $filename();" >> $HEADER


  echo "// Converted from $f" >> $SOURCE
  echo "const char* ShaderChunk::$filename() {" >> $SOURCE
  echo "  return" >> $SOURCE

  while read -r line
  do
    l="$line"
    if [[ ! -z "${l// }" && ! $l == "//"* ]]; then
      echo "    \"$l\\n\"" >> $SOURCE
    fi
  done < "$f"

  echo ";" >> $SOURCE
  echo "}" >> $SOURCE
  echo >> $SOURCE

done

echo "} /* namespace three */" >> $SOURCE

########################################################################
echo "};" >> $HEADER
echo "} /* namespace three */" >> $HEADER
echo "#endif /* THREE_RENDERERS_SHADERS_SHADERCHUNK_H_ */" >> $HEADER


cd -