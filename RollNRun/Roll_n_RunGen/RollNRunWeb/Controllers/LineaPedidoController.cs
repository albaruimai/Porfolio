using System.Collections.Generic;
using System.Linq;
using System.Web.Mvc;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CP.Roll_n_Run;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Assemblers;
using RollNRunWeb.Models;

namespace RollNRunWeb.Controllers
{
    [Authorize]
    public class LineaPedidoController : BasicController
    {
        // GET: LineaPedido
        public ActionResult Index()
        {
            SessionInitialize();
            LineaPedidoCAD linpeCAD = new LineaPedidoCAD(session);
            LineaPedidoCEN linpeCEN = new LineaPedidoCEN(linpeCAD);

            IList<LineaPedidoEN> linpeEN = linpeCEN.ReadAll(0, -1);
            IEnumerable<LineaPedidoViewModel> linpeViewModel = new LineaPedidoAssembler().ConvertListENToModel(linpeEN).ToList();
            SessionClose();

            return View(linpeViewModel);
        }

        // GET: LineaPedido/Details/5
        public ActionResult Details(int id)
        {
            SessionInitialize();
            LineaPedidoCAD linpeCAD = new LineaPedidoCAD(session);
            LineaPedidoCEN linpeCEN = new LineaPedidoCEN(linpeCAD);

            LineaPedidoEN linpeEN = linpeCEN.ReadOID(id);
            LineaPedidoViewModel linpeViewModel = new LineaPedidoAssembler().ConvertENToModelUI(linpeEN);
            SessionClose();

            return View(linpeViewModel);
        }

        // GET: LineaPedido/Create
        public ActionResult Create()
        {
            IList<PedidoEN> lisPeds = new PedidoCEN().ReadAll(0, -1);
            IList<SelectListItem> pedIt = new List<SelectListItem>();

            foreach (PedidoEN ped in lisPeds)
            {
                pedIt.Add(new SelectListItem { Text = ped.Id.ToString(), Value = ped.Id.ToString() });
            }
            ViewData["pedidoId"] = pedIt;

            IList<ProductoEN> lisProds = new ProductoCEN().ReadAll(0, -1);
            IList<SelectListItem> prodIt = new List<SelectListItem>();

            foreach (ProductoEN prod in lisProds)
            {
                prodIt.Add(new SelectListItem { Text = prod.Nombre, Value = prod.Id.ToString() });
            }
            ViewData["productoId"] = prodIt;

            return View();
        }

        // POST: LineaPedido/Create
        [HttpPost]
        public ActionResult Create(LineaPedidoViewModel linpe)
        {
            try
            {
                LineaPedidoCP linpeCP = new LineaPedidoCP();
                LineaPedidoEN linpeEN = linpeCP.New_(linpe.cantidad, linpe.pedidoId, linpe.productoId);



                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: LineaPedido/Edit/5
        public ActionResult Edit(int id)
        {
            SessionInitialize();
            LineaPedidoCAD linpeCAD = new LineaPedidoCAD(session);
            LineaPedidoCEN linpeCEN = new LineaPedidoCEN(linpeCAD);

            LineaPedidoEN linpeEN = linpeCEN.ReadOID(id);
            LineaPedidoViewModel linpeViewModel = new LineaPedidoAssembler().ConvertENToModelUI(linpeEN);

            SessionClose();

            return View(linpeViewModel);
        }

        // POST: LineaPedido/Edit/5
        [HttpPost]
        public ActionResult Edit(int id, LineaPedidoViewModel linpe)
        {
            try
            {
                LineaPedidoCP linpeCP = new LineaPedidoCP();
                LineaPedidoCEN linpeCEN = new LineaPedidoCEN();
                LineaPedidoEN linpeEN = linpeCEN.ReadOID(id);
                linpeCP.Modify(id, linpe.cantidad, linpeEN.Precio);


                return RedirectToAction("Carrito", "Pedido");
            }
            catch
            {
                return View();
            }
        }

        // GET: LineaPedido/Delete/5
        public ActionResult Delete(int id)
        {
            SessionInitialize();
            LineaPedidoCAD linpeCAD = new LineaPedidoCAD(session);
            LineaPedidoCEN linpeCEN = new LineaPedidoCEN(linpeCAD);

            LineaPedidoEN linpeEN = linpeCEN.ReadOID(id);
            LineaPedidoViewModel linpeViewModel = new LineaPedidoAssembler().ConvertENToModelUI(linpeEN);

            SessionClose();

            return View(linpeViewModel);
        }

        // POST: LineaPedido/Delete/5
        [HttpPost]
        public ActionResult Delete(int id, LineaPedidoViewModel linpe)
        {
            try
            {
                LineaPedidoCP linpeCP = new LineaPedidoCP();
                linpeCP.Destroy(id);

                return RedirectToAction("Carrito", "Pedido");
            }
            catch
            {
                return View();
            }
        }
    }
}