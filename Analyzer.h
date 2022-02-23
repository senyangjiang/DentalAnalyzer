#ifndef ANALYZER_H_INCLUDED
#define ANALYZER_H_INCLUDED

#include <QObject>

#include <vector>
#include <unordered_set>

#include "objects.h"
#include "result.h"
#include "parameter.h"

class Analyzer : public QObject
{
    Q_OBJECT

public:
    // main analyze function
    int analyze();

    Parameter param;

signals:
    void msgToConsole(QString msg);

    void updateProgressBar(int val);

    void alertToWindow(QString msg);

private:
    // initialize private variables
    void init();

    // align student model with original model
    mycode::K::Aff_transformation_3 compute_alignment_matrix();

    // select neighboring teeth in the form of (Point,Normal) pair
    void select_neighboring_tooth_pwn(mycode::Mesh &m, std::vector<mycode::Pwn> &pwns, string neighboringToothMargin1, string neighboringToothMargin2);

    // constructing 2d lines from points
    void construct_lines(std::vector<mycode::Point_3> &points, std::vector<mycode::Segment_2> &lines);

    // return true if a 2D point is within a 2D segment set
    bool within_lines(mycode::Point_2 &p, std::vector<mycode::Segment_2> &lines);

    // compute taper (half of toc)
    void compute_taper();

    // compute occlusal reduction
    void compute_occlusal_reduction();

    // compute margin depth
    void compute_margin_depth();

    // compute gingival extension
    void compute_gingival_extension();

    // computes shoulder width
    void compute_shoulder_width();

    // compute axial wall height
    void compute_axial_wall_height();

    // compute roughness
    void compute_roughness();

    // determine what region the point belongs to
    Region region_of(mycode::Point_3 point);

    // select vertices on the occlusal
    void select_occlusal_points(std::unordered_set<mycode::vertex_descriptor> &vertexSet);

    // select vertices on the shoulder
    void select_shoulder_points(std::unordered_set<mycode::vertex_descriptor> &vertexSet);

    // select vertices on the axial wall
    void select_axial_wall_points(std::unordered_set<mycode::vertex_descriptor> &vertexSet);

    // select vertices on tooth
    void select_tooth_points(std::unordered_set<mycode::vertex_descriptor> &vertexSet);

    // report avg, min, max of an array of numbers
    void report_stats(double* avg, const std::vector<mycode::FT> &values);

    // give feedback by comparing value against ruberic
    void feedback();

    bool division_enabled = false; /* debugging variable for disabling division of the tooth into 4 sections */

    mycode::Mesh student_model;
    mycode::Mesh original_model;
    mycode::Polyhedron student_model_poly;
    mycode::Polyhedron original_model_poly;
    mycode::Tree student_tree;
    mycode::Tree original_tree;
    mycode::Point_3 student_model_center;
    mycode::Point_3 student_model_midpoint;
    std::vector<mycode::Point_3> occlusal_points;
    std::vector<mycode::Point_3> axial_points;
    std::vector<mycode::Point_3> margin_points;
    std::vector<mycode::Point_3> gingiva_points;

    Result student_result;
};
#endif