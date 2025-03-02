using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using Roll_n_RunGenNHibernate.CP.Roll_n_Run;
using RollNRunWeb.Models;
using RollNRunWeb.Assemblers;

namespace RollNRunWeb.Controllers
{
    public class BusquedaController : BasicController
    {
        // GET: Busqueda
        public ActionResult Index()
        {
            SessionInitialize();
            ProductoCAD productoCAD = new ProductoCAD(session);
            ProductoCEN productoCEN = new ProductoCEN(productoCAD);

            string peticion = this.Request.RawUrl;
            string[] palabras=peticion.Split('?');
            IList<ProductoEN> productosEN = new List<ProductoEN>();
            if (palabras.Length > 1)
            {
                string[] tipos = palabras[1].Split('=');
                if (tipos.Length > 1)
                {
                    switch (tipos[0])
                    {
                        case "nombre":
                            productosEN = productoCEN.BuscarNombre(tipos[1].Replace("+", " "));
                            break;
                        case "tipo":
                            productosEN = productoCEN.BuscarTipo((Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.Tipo_productoEnum)int.Parse(tipos[1]));
                            break;
                        case "precio":
                            productosEN = productoCEN.BuscarPrecio(Double.Parse(tipos[1].Replace(".", ",")));
                        break;
                    }
                }
                else {
                    productosEN = productoCEN.ReadAll(0, -1);
                }
                
                
            }
            else {
                productosEN = productoCEN.ReadAll(0, -1);
            }

            
            IEnumerable<ProductoViewModel> productosViewModel = new ProductoAssembler().ConvertListENToModel(productosEN).ToList();
            SessionClose();

            return View(productosViewModel);
        }


    }
}
