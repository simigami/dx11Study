#pragma once

template <typename T>
class Geometry
{
public:
    Geometry() {};
    ~Geometry() {};
    
    uint32 GetVertexCount() { return static_cast<uint32>(_vertices.size()); }
    
    void* GetVertexData() { return _vertices.data(); }
    const vector<T>& GetVertex() { return _vertices; }
    
    void* GetIndicesData() { return _indices.data(); }
    const vector<uint32>& GetIndice() { return _indices; }
    uint32 GetIndiceCount() const { return _indices.size(); }
    
    void AddVertex(const T& vertex) { _vertices.push_back(vertex); }
    void InsetVertex(const vector<T>& vertices) { _vertices.insert(_vertices.end(), vertices.begin(), vertices.end()); }
    void SetVertex(const vector<T>& vertices) { _vertices = vertices; }
    
    void AddIndex(uint32 index) { _indices.push_back(index); }
    void SetIndex(const vector<uint32>& indices) { _indices = indices; }
    void InsertIndex(const vector<uint32>& indices){ _indices.insert(_indices.end(), indices.begin(), indices.end()); }
    
private:
    vector<T> _vertices;
    vector<uint32> _indices;
};