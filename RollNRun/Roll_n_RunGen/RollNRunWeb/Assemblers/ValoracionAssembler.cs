using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Models;

namespace RollNRunWeb.Assemblers
{
    public class ValoracionAssembler
    {
        public ValoracionViewModel ConvertENToModelUI(ValoracionEN en)
        {
            ValoracionViewModel val = new ValoracionViewModel();
            val.id = en.Id;
            val.usuario = en.Usuario.Id;
            val.producto = en.Producto.Id;
            val.valor = (int)en.Valor;
            val.comentario = en.Comentario;

            return val;
        }

        public IList<ValoracionViewModel> ConvertListENToModel(IList<ValoracionEN> glup)
        {
            IList<ValoracionViewModel> vals = new List<ValoracionViewModel>();
            foreach (ValoracionEN ugh in glup)
            {
                vals.Add(ConvertENToModelUI(ugh));
            }
            return vals;
        }
    }
}