#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <climits>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

namespace Ui {
class MainWindow;
}

using namespace OpenMesh;
using namespace OpenMesh::Attributes;

struct MyTraits : public OpenMesh::DefaultTraits
{
    // use vertex normals and vertex colors
    VertexAttributes( OpenMesh::Attributes::Normal | OpenMesh::Attributes::Color );
    // store the previous halfedge
    HalfedgeAttributes( OpenMesh::Attributes::PrevHalfedge );
    // use face normals face colors
    FaceAttributes( OpenMesh::Attributes::Normal | OpenMesh::Attributes::Color );
    EdgeAttributes( OpenMesh::Attributes::Color );
    // vertex thickness
    VertexTraits{float thickness; float value;};
    // edge thickness
    EdgeTraits{float thickness;};
};
typedef OpenMesh::TriMesh_ArrayKernelT<MyTraits> MyMesh;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // les fonctions à compléter


    float faceArea(MyMesh* _mesh, int faceID);
    float angleFF(MyMesh *_mesh, int faceID0, int faceID1, int vertID0, int vertID1);
    float angleEE(MyMesh* _mesh, int vertexID, int faceID);
    void H_Curv(MyMesh* _mesh);
    void K_Curv(MyMesh* _mesh);
    float baryArea(MyMesh* _mesh, int vertexID);

    float ecart_angulaire_max(MyMesh* _mesh, int vertexID);
    void Deviation_normales(MyMesh* _mesh);

    void displayMesh(MyMesh *_mesh, bool isTemperatureMap = false, float mapRange = -1);
    void resetAllColorsAndThickness(MyMesh* _mesh);

    bool isFaceTriangle(MyMesh* _mesh, int faceID);
    bool isAllFaceTriangle(MyMesh* _mesh);
    bool hasFaceNeighboors(MyMesh* _mesh, int faceID);
    bool areThereSingleFaces(MyMesh* _mesh);
    bool hasHalfEdgeAFace(MyMesh* _mesh, int halfEdgeID);
    VectorT<unsigned, 37> classifyAngleFF (MyMesh* _mesh);

    VectorT <float,6> boundingBox3D(MyMesh* _mesh);
    VectorT<float,2>  minmaxAreaFace (MyMesh* _mesh);
    void displayFaceAreaFreq (MyMesh* _mesh);

    float totFaceArea(MyMesh* _mesh);

private slots:

    void on_pushButton_chargement_clicked();
    void on_pushButton_angleArea_clicked();
    void on_pushButton_H_clicked();
    void on_pushButton_K_clicked();
    void on_pushButton_D_clicked();

private:

    bool modevoisinage;

    MyMesh mesh;

    int vertexSelection;
    int edgeSelection;
    int faceSelection;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
