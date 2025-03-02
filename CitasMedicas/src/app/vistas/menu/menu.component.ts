import { Component } from '@angular/core';
import {ApiService} from "../../servicios/api/api.service";
import {Router} from "@angular/router";

@Component({
  selector: 'app-menu',
  templateUrl: './menu.component.html',
  styleUrls: ['./menu.component.css']
})
export class MenuComponent {

  tipo:string = "";

  constructor(private api:ApiService, private router:Router) {
  this.tipo = this.api.getTipoToken();
}

  cerrar(){
    this.api.deleteToken();
    this.router.navigate(['login']);
  }

}
