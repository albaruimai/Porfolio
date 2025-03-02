import { Component, OnInit} from '@angular/core';
import {ApiService} from "../../servicios/api/api.service";
import {Router} from "@angular/router";
import {MedicoInterface} from "../../modelos/medico.interface";

@Component({
  selector: 'app-mis-medicos',
  templateUrl: './mis-medicos.component.html',
  styleUrls: ['./mis-medicos.component.css']
})
export class MisMedicosComponent {

  constructor(private api:ApiService, private router:Router) {}

  medicos:MedicoInterface[] = [];

  ngOnInit() {
    this.api.getMisMedicos(this.api.getIdToken()!).subscribe(data =>{
      this.medicos = data;
    });
  }

  verMedico(id: number) {
    this.router.navigate(['verMedico', id]);
  }

}
