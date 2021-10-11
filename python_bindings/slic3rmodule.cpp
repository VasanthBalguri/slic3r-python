#include "slic3rmodule.h"

using namespace Slic3r;
//using namespace boost::python;


    int Slic3rModule::addModel(std::string path)
    {
        std::cout<<"adding 3d model"<<std::endl;
        try {
            model = Model::read_from_file(path);
        } catch (std::exception &e) {
            boost::nowide::cerr << path << ": " << e.what() << std::endl;
            return 1;
        }

        if (model.objects.empty()) {
            boost::nowide::cerr << "Error: file is empty: " << path << std::endl;
            return 1;
        }

        model.add_default_instances();
        std::cout<<"added 3d model"<<std::endl;
        return 0;
    }

    int Slic3rModule::loadConfig(std::string path)
    {
        std::cout<<"loading config"<<std::endl;
        if (!boost::filesystem::exists(path)) {
            boost::nowide::cout << "No such file: " << path << std::endl;
            return 0;
        }

        DynamicPrintConfig c;
        try {
            c.load(path);
        } catch (std::exception &e) {
            boost::nowide::cout << "Error while reading config file: " << e.what() << std::endl;
            return 0;
        }
        c.normalize();
        print_config.apply(c);
        std::cout<<"loaded config"<<std::endl;
        return 0;
    }

    void Slic3rModule::info()
    {
        std::cout<<"help"<<std::endl;
    }
    
    int Slic3rModule::center(float x, float y)
    {
        Pointf p(x,y);
        std::cout<<"set center: "<<x<<" "<<y<<std::endl;
        model.center_instances_around_point(p);
        return 0;
    }

    int Slic3rModule::translate(float x,float y,float z){
        std::cout<<"translate: "<<x<<" "<<y<<" "<<z<<std::endl;
        model.translate(x,y,z);
        
        return 0;
    }

    int Slic3rModule::rotate(float rx,float ry,float rz)
    {
        std::cout<<"rotate: "<<rx<<" "<<ry<<" "<<rz<<std::endl;
        for (ModelObject* o : model.objects) {

            o->rotate(Geometry::deg2rad(rx), X);
            o->rotate(Geometry::deg2rad(ry), Y);
            o->rotate(Geometry::deg2rad(rz), Z);
        }

        return 0;
    }

    int Slic3rModule::scale(float scale)
    {
        std::cout<<"scale: "<<scale<<std::endl;
        for (ModelObject* o : model.objects) {

                o->scale(scale);
        }
        
        return 0;
    }

    int Slic3rModule::scaleToFit(float x, float y,float z)
    {
        std::cout<<"scale to volume: "<<x<<" "<<y<<" "<<z<<std::endl;
        for (ModelObject* o : model.objects) {
            if (x > 0.0 && y > 0.0 && z > 0.0 )
            {
                Sizef3 s(x,y,z);
                o->scale_to_fit(s);
            }
            else
            {
                std::cout<<"-ve volume"<<std::endl;
                return 1;
            }
        }

        return 0;
    }

    int Slic3rModule::slice(std::string output_file, float centerX, float centerY)
    {
       std::cout<<"slice"<<std::endl;
       Print print;

       if(!model.objects.empty())
       {
           model.arrange_objects(print.config.min_object_distance());
           Pointf p(centerX,centerY);
           model.center_instances_around_point(p);
           if (output_file.empty()) output_file = model.objects.front()->input_file + ".gcode";
                print.apply_config(print_config);

           for (auto* mo : model.objects) {
                print.auto_assign_extruders(mo);
                print.add_model_object(mo);
           }
           print.validate();
           print.export_gcode(output_file);
           estimatedMaterial = print.total_used_filament;
           estimatedWeight = print.total_weight;
           estimatedCost = print.total_cost;
           std::cout<<"exported to "<<output_file<<std::endl;
       }else
       {
           std::cout<<"empty"<<output_file<<std::endl;
       }
        return 0;
    }

   int Slic3rModule::export3MF(std::string output_file)
    {
        std::string outfile = output_file;
        std::cout<<"export to "<<outfile<<std::endl;
        if (outfile.empty()) outfile = model.objects.front()->input_file;
        // Check if the file is already a 3mf.
        if(outfile.substr(outfile.find_last_of('.'), outfile.length()) == ".3mf")
            outfile = outfile.substr(0, outfile.find_last_of('.')) + "_2" + ".3mf";
        else
            // Remove the previous extension and add .3mf extention.
            outfile = outfile.substr(0, outfile.find_last_of('.')) + ".3mf";
        IO::TMF::write(model, outfile);
        boost::nowide::cout << "File file exported to " << outfile << std::endl;
        return 0;
    }

    int Slic3rModule::exportObj(std::string output_file)
    {
        std::string outfile = output_file;
        std::cout<<"export to "<<outfile<<std::endl;
        if (outfile.empty()) outfile = model.objects.front()->input_file + ".obj";

        TriangleMesh mesh = model.mesh();
        mesh.repair();
        IO::OBJ::write(mesh, outfile);
        boost::nowide::cout << "File exported to " << outfile << std::endl;
        return 0;
    }

    int Slic3rModule::exportSvg(std::string output_file)
    {
        std::string outfile = output_file;
        std::cout<<"export to "<<outfile<<std::endl;
        if (outfile.empty())
            outfile = model.objects.front()->input_file + ".svg";

        SLAPrint print(&model); // initialize print with model
        print.config.apply(print_config, true); // apply configuration
        print.slice(); // slice file
        print.write_svg(outfile); // write SVG
        boost::nowide::cout << "SVG file exported to " << outfile << std::endl;
        return 0;
    }

    int Slic3rModule::exportPov(std::string output_file)
    {
        std::string outfile = output_file;
        std::cout<<"export to "<<outfile<<std::endl;
        if (outfile.empty()) outfile = model.objects.front()->input_file + ".pov";

        TriangleMesh mesh = model.mesh();
        mesh.repair();
        IO::POV::write(mesh, outfile);
        boost::nowide::cout << "File exported to " << outfile << std::endl;
        return 0;
    }
