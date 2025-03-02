using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Models;

namespace RollNRunWeb.Assemblers
{
    public class SubforoAssembler
    {
        public SubforoViewModel ConvertENToModelUI(SubforoEN en)
        {
            SubforoViewModel dir = new SubforoViewModel();
            dir.id = en.Id;
            int cont = 0;
            dir.usuario = en.Usuarios;
            dir.Seguidores = en.Usuarios.Count;
            dir.Autor = en.Autor.Nickname;
            dir.Titulo = en.Titulo;
            dir.Fecha = (DateTime)en.Fecha;
            dir.Descripcion = en.Descripcion;
            dir.NumEntradas = en.NumEntradas;

            return dir;
        }

        public IList<SubforoViewModel> ConvertListENToModel(IList<SubforoEN> glup)
        {
            IList<SubforoViewModel> dirs = new List<SubforoViewModel>();
            foreach (SubforoEN ugh in glup)
            {
                dirs.Add(ConvertENToModelUI(ugh));
            }
            return dirs;
        }
    }
}