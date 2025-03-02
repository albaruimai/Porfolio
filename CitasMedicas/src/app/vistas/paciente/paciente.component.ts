import {Component, OnInit} from '@angular/core';
import {ApiService} from "../../servicios/api/api.service";
import {Router} from "@angular/router";
import {PacienteInterface} from "../../modelos/paciente.interface";

@Component({
  selector: 'app-paciente',
  templateUrl: './paciente.component.html',
  styleUrls: ['./paciente.component.css']
})
export class PacienteComponent implements  OnInit{

  constructor(private api:ApiService, private router:Router) {}

  pacientes:PacienteInterface[] = [];
  ngOnInit() {
    this.api.getAllPacientes().subscribe(data =>{
      this.pacientes = data;
    });
  }

  verPaciente(id: number) {
    this.router.navigate(['verPaciente', id]);
  }

  editarPaciente(id:number){
    this.router.navigate(['editarPaciente', id]);
  }

  nuevoPaciente(){
    this.router.navigate(['nuevoPaciente']);
  }

}
