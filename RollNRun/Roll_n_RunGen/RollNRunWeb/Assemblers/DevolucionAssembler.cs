using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Models;

namespace RollNRunWeb.Assemblers
{
    public class DevolucionAssembler
    {
        public DevolucionViewModel ConvertENToModelUI(DevolucionEN en)
        {
            DevolucionViewModel dir = new DevolucionViewModel();
            dir.id = en.Id;
            dir.Motivo = en.Motivo;
            dir.Descripcion = en.Descripcion;

            return dir;
        }

        public IList<DevolucionViewModel> ConvertListENToModel(IList<DevolucionEN> glup)
        {
            IList<DevolucionViewModel> dirs = new List<DevolucionViewModel>();
            foreach (DevolucionEN ugh in glup)
            {
                dirs.Add(ConvertENToModelUI(ugh));
            }
            return dirs;
        }

    }
}