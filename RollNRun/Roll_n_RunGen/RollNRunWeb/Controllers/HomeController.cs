using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Assemblers;
using RollNRunWeb.Models;

namespace RollNRunWeb.Controllers
{
    public class HomeController : BasicController
    {
        public ActionResult Index()
        {
            SessionInitialize();
            ProductoCAD productoCAD = new ProductoCAD(session);
            ProductoCEN productoCEN = new ProductoCEN(productoCAD);

            IList<ProductoEN> productosEN = productoCEN.ReadAll(0, -1);
            IList<ProductoEN> prodEN = new List<ProductoEN>();

            foreach (ProductoEN prod in productosEN)
            {
                if (prod.Oferta == 0)
                {
                    prodEN.Add(prod);
                }
            }

            IEnumerable<ProductoViewModel> productosViewModel = new ProductoAssembler().ConvertListENToModel(prodEN).ToList();
            SessionClose();

            return View(productosViewModel);
        }

        public ActionResult Ofertas()
        {
            SessionInitialize();
            ProductoCAD productoCAD = new ProductoCAD(session);
            ProductoCEN productoCEN = new ProductoCEN(productoCAD);

            IList<ProductoEN> productosEN = productoCEN.BuscarOfertas();
            IEnumerable<ProductoViewModel> productosViewModel = new ProductoAssembler().ConvertListENToModel(productosEN).ToList();
            SessionClose();

            return PartialView(productosViewModel);
        }

        public ActionResult About()
        {
            ViewBag.Message = "Your application description page.";

            return View();
        }

        public ActionResult Contact()
        {
            ViewBag.Message = "Your contact page.";

            return View();
        }
    }
}