xof 0303txt 0032
template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}


Mesh Box01 {
 6;
 -19.685040;-19.685040;0.000000;,
 -19.685040;19.685040;0.000000;,
 19.685040;19.685040;0.000000;,
 19.685040;19.685040;0.000000;,
 19.685040;-19.685040;0.000000;,
 -19.685040;-19.685040;0.000000;;
 2;
 3;0,1,2;,
 3;3,4,5;;

 MeshNormals  {
  6;
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;;
  2;
  3;0,1,2;,
  3;3,4,5;;
 }

 MeshTextureCoords  {
  6;
  0.003996;0.996002;,
  0.003998;-6.996004;,
  7.996004;-6.996002;,
  7.996004;-6.996002;,
  7.996002;0.996004;,
  0.003996;0.996002;;
 }
}