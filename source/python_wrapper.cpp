#include<boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
using namespace boost::python;

#include"polyhedron.h"

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS( make_sphere_overloads,		initialize_create_sphere,    1, 4 );
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS( make_box_overloads,			initialize_create_box,       3, 4 );
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS( make_cylinder_overloads,    initialize_create_cylinder,  2, 4 );
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS( make_cone_overloads,		initialize_create_cone,      2, 4 );
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS( make_torus_overloads,		initialize_create_torus,     2, 5 );
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS( make_extrusion_overloads,		initialize_create_extrusion,     3,3 );

BOOST_PYTHON_FUNCTION_OVERLOADS( sphere_overloads,   sphere,   1, 4 );
BOOST_PYTHON_FUNCTION_OVERLOADS( box_overloads,      box,      3, 4 );
BOOST_PYTHON_FUNCTION_OVERLOADS( cylinder_overloads, cylinder, 2, 4 );
BOOST_PYTHON_FUNCTION_OVERLOADS( cone_overloads,     cone,     2, 4 );
BOOST_PYTHON_FUNCTION_OVERLOADS( torus_overloads,    torus,    2, 5 );
BOOST_PYTHON_FUNCTION_OVERLOADS( extrusion_overloads,    extrusion,    3,3 );

BOOST_PYTHON_MODULE(pyPolyCSG){
	numeric::array::set_module_and_type("numpy", "ndarray");
    
	def( "load_mesh",        load_mesh_file );
	def( "sphere",		     sphere,    sphere_overloads() );
	def( "box",			     box,       box_overloads() );
	def( "cylinder",	     cylinder,  cylinder_overloads() );
	def( "cone",		     cone,      cone_overloads() );
	def( "torus",		     torus,     torus_overloads() );
	def( "extrusion",		     extrusion,     extrusion_overloads() );
	
	class_<polyhedron>("polyhedron")
	.def( "load_mesh",	               &polyhedron::initialize_load_from_file )
	.def( "make_sphere",               &polyhedron::initialize_create_sphere, make_sphere_overloads() )
	.def( "make_box",                  &polyhedron::initialize_create_box,    make_box_overloads() )
	.def( "make_cone",                 &polyhedron::initialize_create_cone,   make_cone_overloads() )
	.def( "make_torus",                &polyhedron::initialize_create_torus,  make_torus_overloads() )
	.def( "make_cylinder",                &polyhedron::initialize_create_cylinder,  make_cylinder_overloads() )
	.def( "make_extrusion",                &polyhedron::initialize_create_extrusion,  make_extrusion_overloads() )
	.def( "translate",                 &polyhedron::translate )
	.def( "rotate",                    &polyhedron::rotate )
	.def( "scale",                     &polyhedron::scale )
	.def( "save_mesh",                 &polyhedron::output_store_in_file )
  .def( "load_from_lists",           &polyhedron::initialize_load_from_mesh )
    
    .def( "num_vertices",              &polyhedron::num_vertices )
    .def( "num_faces",                 &polyhedron::num_faces )
    .def( "num_face_vertices",         &polyhedron::num_face_vertices )
    .def( "get_vertex",                &polyhedron::py_get_vertex_coordinates )
    .def( "get_face",                  &polyhedron::py_get_face_vertices )
    .def( "get_vertices",              &polyhedron::py_get_vertices )
    .def( "get_triangles",             &polyhedron::py_get_triangles )
	
	.def( self + polyhedron() )
	.def( self - polyhedron() )
	.def( self * polyhedron() )
	;

boost::python::class_<std::vector<double> >("DoubleVec")
  .def(boost::python::vector_indexing_suite<std::vector<double> >());
boost::python::class_<std::vector<int> >("IntVec")
  .def(boost::python::vector_indexing_suite<std::vector<int> >());
}

