import {Component, OnInit} from '@angular/core';
import {ApiService} from "../../servicios/api/api.service";
import {Router} from "@angular/router";
import {MedicoInterface} from "../../modelos/medico.interface";

@Component({
  selector: 'app-medico',
  templateUrl: './medico.component.html',
  styleUrls: ['./medico.component.css']
})
export class MedicoComponent implements  OnInit{

  constructor(private api:ApiService, private router:Router) {}

  medicos:MedicoInterface[] = [];
  ngOnInit() {
    this.api.getAllMedicos().subscribe(data =>{
      this.medicos = data;
    });
  }
  verMedico(id: number) {
    this.router.navigate(['verMedico', id]);
  }

  editarMedico(id:number){
    this.router.navigate(['editarMedico', id]);
  }

  nuevoMedico(){
    this.router.navigate(['nuevoMedico']);
  }

}
