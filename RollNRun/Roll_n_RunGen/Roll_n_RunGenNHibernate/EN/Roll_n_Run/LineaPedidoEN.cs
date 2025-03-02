
using System;
// Definición clase LineaPedidoEN
namespace Roll_n_RunGenNHibernate.EN.Roll_n_Run
{
public partial class LineaPedidoEN
{
/**
 *	Atributo cantidad
 */
private int cantidad;



/**
 *	Atributo precio
 */
private double precio;



/**
 *	Atributo id
 */
private int id;



/**
 *	Atributo pedido
 */
private Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN pedido;



/**
 *	Atributo producto
 */
private Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN producto;






public virtual int Cantidad {
        get { return cantidad; } set { cantidad = value;  }
}



public virtual double Precio {
        get { return precio; } set { precio = value;  }
}



public virtual int Id {
        get { return id; } set { id = value;  }
}



public virtual Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN Pedido {
        get { return pedido; } set { pedido = value;  }
}



public virtual Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN Producto {
        get { return producto; } set { producto = value;  }
}





public LineaPedidoEN()
{
}



public LineaPedidoEN(int id, int cantidad, double precio, Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN pedido, Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN producto
                     )
{
        this.init (Id, cantidad, precio, pedido, producto);
}


public LineaPedidoEN(LineaPedidoEN lineaPedido)
{
        this.init (Id, lineaPedido.Cantidad, lineaPedido.Precio, lineaPedido.Pedido, lineaPedido.Producto);
}

private void init (int id
                   , int cantidad, double precio, Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN pedido, Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN producto)
{
        this.Id = id;


        this.Cantidad = cantidad;

        this.Precio = precio;

        this.Pedido = pedido;

        this.Producto = producto;
}

public override bool Equals (object obj)
{
        if (obj == null)
                return false;
        LineaPedidoEN t = obj as LineaPedidoEN;
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
