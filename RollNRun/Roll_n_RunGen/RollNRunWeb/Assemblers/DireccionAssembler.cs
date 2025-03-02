using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Models;

namespace RollNRunWeb.Assemblers
{
    public class DireccionAssembler
    {
        public DireccionViewModel ConvertENToModelUI(DireccionEN en)
        {
            DireccionViewModel dir = new DireccionViewModel();
            dir.id = en.Id;
            dir.Provincia = en.Provincia;
            dir.Localidad = en.Localidad;
            dir.CP = en.Cp;
            dir.Calle = en.Calle;

            return dir;
        }

        public IList<DireccionViewModel> ConvertListENToModel(IList<DireccionEN> glup)
        {
            IList<DireccionViewModel> dirs = new List<DireccionViewModel>();
            foreach(DireccionEN ugh in glup)
            {
                dirs.Add(ConvertENToModelUI(ugh));
            }
            return dirs;
        }
    }
}