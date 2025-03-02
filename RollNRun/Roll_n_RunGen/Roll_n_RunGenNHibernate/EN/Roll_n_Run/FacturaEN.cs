
using System;
// Definición clase FacturaEN
namespace Roll_n_RunGenNHibernate.EN.Roll_n_Run
{
public partial class FacturaEN
{
/**
 *	Atributo fecha
 */
private Nullable<DateTime> fecha;



/**
 *	Atributo precio
 */
private double precio;



/**
 *	Atributo metodoPago
 */
private Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.PagoEnum metodoPago;



/**
 *	Atributo id
 */
private int id;



/**
 *	Atributo pedido
 */
private Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN pedido;



/**
 *	Atributo fechaFacturacion
 */
private Nullable<DateTime> fechaFacturacion;






public virtual Nullable<DateTime> Fecha {
        get { return fecha; } set { fecha = value;  }
}



public virtual double Precio {
        get { return precio; } set { precio = value;  }
}



public virtual Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.PagoEnum MetodoPago {
        get { return metodoPago; } set { metodoPago = value;  }
}



public virtual int Id {
        get { return id; } set { id = value;  }
}



public virtual Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN Pedido {
        get { return pedido; } set { pedido = value;  }
}



public virtual Nullable<DateTime> FechaFacturacion {
        get { return fechaFacturacion; } set { fechaFacturacion = value;  }
}





public FacturaEN()
{
}



public FacturaEN(int id, Nullable<DateTime> fecha, double precio, Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.PagoEnum metodoPago, Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN pedido, Nullable<DateTime> fechaFacturacion
                 )
{
        this.init (Id, fecha, precio, metodoPago, pedido, fechaFacturacion);
}


public FacturaEN(FacturaEN factura)
{
        this.init (Id, factura.Fecha, factura.Precio, factura.MetodoPago, factura.Pedido, factura.FechaFacturacion);
}

private void init (int id
                   , Nullable<DateTime> fecha, double precio, Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.PagoEnum metodoPago, Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN pedido, Nullable<DateTime> fechaFacturacion)
{
        this.Id = id;


        this.Fecha = fecha;

        this.Precio = precio;

        this.MetodoPago = metodoPago;

        this.Pedido = pedido;

        this.FechaFacturacion = fechaFacturacion;
}

public override bool Equals (object obj)
{
        if (obj == null)
                return false;
        FacturaEN t = obj as FacturaEN;
        if (t == null)
                return false;
        if (Id.Equals (t.Id))
                return true;
        else
                return false;
}

public override int GetHashCode ()
{
        int hash = 13;

        hash += this.Id.GetHashCode ();
        return hash;
}
}
}
