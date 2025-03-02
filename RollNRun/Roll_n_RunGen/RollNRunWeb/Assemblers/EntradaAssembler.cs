using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Models;

namespace RollNRunWeb.Assemblers
{
    public class EntradaAssembler
    {
        public EntradaViewModel ConvertENToModelUI(EntradaEN en)
        {
            EntradaViewModel dir = new EntradaViewModel();
            dir.id = en.Id;
            dir.idSubforo = en.Subforo.Id;
            dir.Subforo = en.Subforo.Titulo;
            dir.idUsuario = en.Usuario.Id;
            dir.Usuario = en.Usuario.Nickname;
            dir.Texto = en.Texto;

            return dir;
        }

        public IList<EntradaViewModel> ConvertListENToModel(IList<EntradaEN> glup)
        {
            IList<EntradaViewModel> dirs = new List<EntradaViewModel>();
            foreach (EntradaEN ugh in glup)
            {
                dirs.Add(ConvertENToModelUI(ugh));
            }
            return dirs;
        }
    }
}