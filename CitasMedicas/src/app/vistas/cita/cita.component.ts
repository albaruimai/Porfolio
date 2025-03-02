import {Component, OnInit} from '@angular/core';
import {ApiService} from "../../servicios/api/api.service";
import {Router} from "@angular/router";
import {CitaInterface} from "../../modelos/cita.interface";

@Component({
  selector: 'app-cita',
  templateUrl: './cita.component.html',
  styleUrls: ['./cita.component.css']
})
export class CitaComponent  implements  OnInit{

  constructor(private api:ApiService, private router:Router) {}

  citas:CitaInterface[] = [];
  ngOnInit() {
    this.api.getAllCitas().subscribe(data =>{
      this.citas = data;
    });
  }

  verCita(id: number) {
    this.router.navigate(['verCita', id]);
  }

  editarCita(id:number){
    this.router.navigate(['editarCita', id]);
  }

  nuevaCita(){
    this.router.navigate(['nuevaCita']);
  }

}
