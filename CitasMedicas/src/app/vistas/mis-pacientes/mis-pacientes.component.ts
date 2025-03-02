import { Component, OnInit} from '@angular/core';
import {ApiService} from "../../servicios/api/api.service";
import {Router} from "@angular/router";
import {PacienteInterface} from "../../modelos/paciente.interface";

@Component({
  selector: 'app-mis-pacientes',
  templateUrl: './mis-pacientes.component.html',
  styleUrls: ['./mis-pacientes.component.css']
})
export class MisPacientesComponent implements  OnInit{

  constructor(private api:ApiService, private router:Router) {}

  pacientes:PacienteInterface[] = [];
    ngOnInit() {
      this.api.getMisPacientes(this.api.getIdToken()).subscribe(data =>{
      this.pacientes = data;
    });
  }

  verPaciente(id: number) {
    this.router.navigate(['verPaciente', id]);
  }

}
