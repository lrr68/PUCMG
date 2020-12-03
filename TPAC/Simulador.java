import java.io.*;
import java.util.ArrayList;

/*TODO
 *Buffer de reordenamento
 */

public class Simulador{
	public static int numUla;   		//numero de ulas
	public static int numMul;   		//numero de multiplicadores
	public static int numLS;    		//load e store
	public static int numBr;    		//branches(desvios)
	public static int numCiclos;		//numero de ciclos gastos
	public static int tamJanela;		//tamanho da janela
	public static Instrucao[] janela;   //janela de instruções
	public static ArrayList<Instrucao> mem = new ArrayList<Instrucao>();		//instruções da memória 

	public static Instrucao[] ula;
	public static Instrucao[] mul;
	public static Instrucao[] ls ;
	public static Instrucao[] br ;


	public static void main(String[] args){
		loadConfig();
		ula = new Instrucao[numUla];
		mul = new Instrucao[numMul];
		ls = new Instrucao[numLS];
		br = new Instrucao[numBr];
		janela = new Instrucao[tamJanela];
		while(!mem.isEmpty() || numInst() > 1){
			instructionDecode();
			printJ();
			instructionDispatch();
			print();
			execute();
			try{
				System.in.read();
			}catch (IOException e){}
		}
	}

	public static void execute(){
		//executa as intrucoes nas unidades
		for(int j=0; j < numUla;j++ ){
			if(ula[j]!=null){
				ula[j].ciclos = ula[j].ciclos -1;
				if(ula[j].ciclos == 0)
					ula[j] = null;
			}
		}

		for(int j=0; j < numMul;j++ ){
			if(mul[j]!=null){
				mul[j].ciclos = mul[j].ciclos -1;
				if(mul[j].ciclos == 0)
					mul[j] = null;
			}
		}
		for(int j=0; j < numLS;j++ ){
			if(ls[j]!=null){
				ls[j].ciclos = ls[j].ciclos -1;
				if(ls[j].ciclos == 0)
					ls[j] = null;
			}
		}
		for(int j=0; j < numBr; j++){
			if(br[j]!=null){
				br[j].ciclos = br[j].ciclos -1;
				if(br[j].ciclos == 0)
					br[j] = null;
			}
		}

	}

	public static void loadConfig(){
		BufferedReader br = null;
		try{
			br = new BufferedReader(new FileReader("configuracoes.txt"));
			numUla = Integer.parseInt(br.readLine().split(" ")[1]);
			numMul = Integer.parseInt(br.readLine().split(" ")[1]);
			numLS =  Integer.parseInt(br.readLine().split(" ")[1]);
			numBr =  Integer.parseInt(br.readLine().split(" ")[1]);
			tamJanela =  Integer.parseInt(br.readLine().split(" ")[1]);
			br.readLine();
			//Instruction Fetch
			String instrucao = br.readLine();
			while(instrucao != null){
				Instrucao i = new Instrucao(instrucao);
				mem.add(i);
				instrucao = br.readLine();
			}
		}catch(Exception e){
			e.printStackTrace();
		}finally{
			try{
				br.close();
			}catch(Exception e){}
		}
	}

	public static void instructionDecode(){
		if ((numInst() + 2) <= tamJanela) {       // confere se cabem pelo menos mais duas instrucoes na janela
			for(int x = 0; !mem.isEmpty() && x < 2; x++) {
				Instrucao instObj = mem.get(0);
				if (instObj.OP.charAt(0) != 'l') {
					instObj.ciclos = 1;
				} // fim if
				else {
					instObj.ciclos= 2;
				} // fim else
				int i =0;
				while(i < tamJanela && janela[i] != null){
					i++;
				}
				if(i < tamJanela){
					janela[i] = instObj;
					mem.remove(instObj);
				}
			} // fim for
		} // fim if
	} // fim instructionDecode

	public static void dependsOnJanela(Instrucao instObj){
		for(int i = 0; i < tamJanela; i++){
			if(janela[i] != null){
				switch(instObj.OP.charAt(0)){
					case 'm': 
					case 'b':
					case 'a': if(instObj.r2.equals(janela[i].r1) || instObj.r3.equals(janela[i].r1)){
								  instObj.depende = janela[i];
								  instObj.tipoDepend = true;
							  }else if(instObj.r1.equals(janela[i].r1)){
								  instObj.depende = janela[i];
								  instObj.inst = instObj.OP+" rA,"+instObj.r2+instObj.r3;
							  }
							  break;
					case 'l': if(instObj.r2.equals(janela[i].r1)){
								  instObj.depende = janela[i];
								  instObj.tipoDepend = true;
							  }else if(instObj.r1.equals(janela[i].r1)){
								  instObj.depende = janela[i];
								  instObj.inst = instObj.OP+" rB,"+instObj.r2+"("+instObj.r3+")";
							  }
							  break;
					case 's': if(instObj.OP.charAt(1) == 'u'){
								  if(instObj.r2.equals(janela[i].r1 )|| instObj.r3.equals(janela[i].r1)){
									  instObj.depende = janela[i];
									  instObj.tipoDepend = true;
								  }else if(instObj.r1.equals(janela[i].r1)){
									  instObj.depende = janela[i];
									  instObj.inst = instObj.OP+" rC,"+instObj.r2+instObj.r3;
								  }
							  }else{
								  if(instObj.r1.equals(janela[i].r1)){
									  instObj.depende = janela[i];
									  instObj.tipoDepend = true;
								  }else if(instObj.r2.equals(janela[i].r1)){
									  instObj.depende = janela[i];
									  instObj.inst = instObj.OP+" "+instObj.r1+","+instObj.r2+"(rD)";
								  }
							  }
							  break;
				}
			}
		}
	}

	public static void dependsDispatch(Instrucao instObj) {
		switch(instObj.OP.charAt(0)){
			case 'a':
				for(int z=0; z<numUla; z++){
					if(ula[z] !=null){
						if(instObj.r2.equals(ula[z].r1) || instObj.r3.equals(ula[z].r1)){
							instObj.depende = ula[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r1.equals(ula[z].r1)){
							instObj.depende = ula[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}  
				}
				for(int z=0; z<numMul; z++){
					if(mul[z] !=null){
						if(instObj.r2.equals(mul[z].r1) || instObj.r3.equals(mul[z].r1)){
							instObj.depende = mul[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r1.equals(mul[z].r1)){
							instObj.depende = mul[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}  
				}
				for(int z=0; z<numLS; z++){
					if(ls[z] !=null){
						if(instObj.r3.equals(ls[z].r1)){
							instObj.depende = ls[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r1.equals(ls[z].r1)){
							instObj.depende = ls[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}  
				}
				for(int z=0; z<numBr; z++){
					if(br[z] !=null){
						if(instObj.r2.equals(br[z].r1) || instObj.r3.equals(br[z].r1)){
							instObj.depende = br[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r1 == br[z].r1){
							instObj.depende = br[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}  
				}
				break;
			case 'l':
				for(int z=0;z<numUla;z++){
					if(ula[z] !=null){
						if(instObj.r2.equals(ula[z].r1)){
							instObj.depende = ula[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r1.equals(ula[z].r1)){
							instObj.depende = ula[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}

				}  
				for(int z=0;z<numMul;z++){
					if(mul[z] !=null){
						if(instObj.r2.equals(mul[z].r1)){
							instObj.depende = mul[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r1.equals(mul[z].r1)){
							instObj.depende = mul[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}
				}
				for(int z=0;z<numLS;z++){
					if(ls[z] !=null){
						if( instObj.r1.equals(ls[z].r2) ||instObj.r2.equals(ls[z].r1)  ){
							instObj.depende = ls[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r1.equals(ls[z].r1)){
							instObj.depende = ls[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}

				}
				for(int z=0;z<numBr;z++){
					if(br[z] !=null){
						if( instObj.r1.equals(br[z].r2) ||instObj.r2.equals(br[z].r1)  ){
							instObj.depende = br[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r1.equals(br[z].r1)){
							instObj.depende = br[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}

				}
				break;
			case 'm':
				for(int z=0; z<numUla; z++){
					if(ula[z] !=null){
						if(instObj.r2.equals(ula[z].r1) || instObj.r3.equals(ula[z].r1)){
							instObj.depende = ula[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r1.equals(ula[z].r1)){
							instObj.depende = ula[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}  
				}
				for(int z=0; z<numMul; z++){
					if(mul[z] !=null){
						if(instObj.r2.equals(mul[z].r1) || instObj.r3.equals(mul[z].r1)){
							instObj.depende = mul[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r1.equals(mul[z].r1)){
							instObj.depende = mul[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}  
				}
				for(int z=0; z<numLS; z++){
					if(ls[z] !=null){
						if(instObj.r2.equals(ls[z].r1) || instObj.r3.equals(ls[z].r1)){
							instObj.depende = ls[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r1.equals(ls[z].r1)){
							instObj.depende = ls[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}  
				}
				for(int z=0; z<numBr; z++){
					if(br[z] !=null){
						if(instObj.r2.equals(br[z].r1) || instObj.r3.equals(br[z].r1)){
							instObj.depende = br[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r1.equals(br[z].r1)){
							instObj.depende = br[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}  
				}

				break;
			case 's':

				for(int z=0;z<numUla;z++){
					if(ula[z] !=null){
						if(instObj.r1.equals(ula[z].r1)){
							instObj.depende = ula[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r2.equals(ula[z].r1)){
							instObj.depende = ula[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}

				}
				for(int z=0;z<numMul;z++){
					if(mul[z] !=null){
						if(instObj.r1.equals(mul[z].r1)){
							instObj.depende = mul[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r2.equals(mul[z].r1)){
							instObj.depende = mul[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}

				}  
				for(int z=0;z<numLS;z++){
					if(ls[z] !=null){
						if( instObj.r1.equals(ls[z].r2) ||instObj.r2.equals(ls[z].r1)  ){
							instObj.depende = ls[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r1.equals(ls[z].r1)){
							instObj.depende = ls[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}
				}
				for(int z=0;z<numBr;z++){
					if(br[z] !=null){
						if( instObj.r1.equals(br[z].r2 )||instObj.r2.equals(br[z].r1)  ){
							instObj.depende = br[z];
							instObj.tipoDepend = true;
						}
						else if(instObj.r1.equals(br[z].r1)){
							instObj.depende = br[z];
						}else{
							instObj.depende = null;
							instObj.tipoDepend = false;
						}
					}
				}

				break;
		}


	}




	public static void instructionDispatch(){
		for(int i =0; i < tamJanela; i++){
			Instrucao inst = janela[i];
			if (inst != null){	
				//dependsDispatch(inst);
				//System.out.println(inst.depende);
				//if((inst.depende != null && !inst.tipoDepend) || inst.depende == null){
					//se for dependencia falsa ou nao for dependencia
					switch(inst.OP.charAt(0)){
						case 'a': ULADispatch(inst);
								  break;
						case 'l': LSDispatch(inst);
								  break;
						case 'm': MULDispatch(inst);
								  break;
						case 's': if(inst.OP.charAt(1) == 'u'){
									  ULADispatch(inst);  
								  }else{
									  LSDispatch(inst);
								  }
								  break;
						case 'b':BRDispatch(inst);
								 break;
					}
				//}
			}
		}
	}

	public static int numInst(){
		int i = 0;
		for(int j =0; j<tamJanela;j++){
			if(janela[j] != null)
				i++;
		}
		return i;
	}

	public static void ULADispatch(Instrucao i){
		for(int k =0; k<numUla;k++){
			if(ula[k] == null){
				ula[k] = i;
				delete(i);
				break;
			}
		}
	}

	public static void MULDispatch(Instrucao i){
		for(int k =0; k<numMul;k++){
			if(mul[k] == null){
				mul[k] = i;
				delete(i);
				break;
			}
		}
	}

	public static void LSDispatch(Instrucao i){
		for(int k =0; k<numLS;k++){
			if(ls[k] == null){
				ls[k] = i;
				delete(i);
				break;
			}
		}
	}

	public static void BRDispatch(Instrucao i){
		for(int k =0; k<numBr;k++){
			if(br[k] == null){
				br[k] = i;
				delete(i);
				break;
			}
		}
	}

	public static void delete(Instrucao i){
		for(int k=0;k<tamJanela;k++){
			if(janela[k]==i){
				janela[k] = null;
			}
		}
	}

	public static void printJ(){
		System.out.println("+----Janela------+");
		for(int i = 0; i<numInst(); i++){
			if(janela[i] != null)
				System.out.println(janela[i].inst);
		}
	}

	public static void print(){
		
		System.out.println("+--------Despacho---------+");
		for(int j = 0; j<numUla;j++){
			System.out.print("Somador ("+(j+1)+")      |      ");
		}

		for(int j = 0; j<numMul;j++){
			System.out.print("Multiplicador ("+(j+1)+")      |      ");
		}

		for(int j = 0; j<numLS;j++){
			System.out.print("Load/Store ("+(j+1)+")      |      ");
		}
		for(int j = 0; j<numBr;j++){
			System.out.print("Branches ("+(j+1)+")      |      ");
		}
		System.out.print("\n");
		for(int j=0; j < numUla;j++ ){
			if(ula[j]!=null){
				System.out.print(ula[j].inst+"     |      ");
			}else{
				System.out.print("                 |      ");
			}
		}
		for(int j=0; j < numMul;j++ ){
			if(mul[j]!=null){
				System.out.print(mul[j].inst+"          |      ");
			}else{
				System.out.print("                       |      ");
			}
		}
		for(int j=0; j < numLS;j++ ){
			if(ls[j]!=null){
				System.out.print(ls[j].inst+"        |     ");
			}else{
				System.out.print("            |     ");
			}
		}
		for(int j=0; j < numBr;j++ ){
			if(br[j]!=null){
				System.out.print(br[j].inst+"      |     ");
			}else{
				System.out.print("                   |     ");
			}
		}
		System.out.print("\n");
		System.out.print("\n");
		System.out.print("\n");
		System.out.print("-------------------------------------------------------------------------------------------------------------");
		System.out.print("\n");
		System.out.print("\n");
	}





} // fim class

class Instrucao{
	String OP;
	String r1, r2, r3;
	String inst;
	int ciclos;
	Instrucao depende;
	boolean tipoDepend;

	Instrucao(String inst){
		String ins[] = inst.split(" ");
		String OP = ins[0];
		String regs[] = ins[1].split(",");
		String r1;
		String r2;
		String r3;
		if(OP.charAt(0) == 's' && OP.charAt(1) == 'w' || OP.charAt(0) == 'l'){
			r1 = regs[0];
			String r[] = regs[1].replace("(",";").replace(")","").split(";");
			r2 = r[1];
			r3 = r[0];
		}else{
			r1 = regs[0];
			r2 = regs[1];
			r3 = regs[2];
		}
		this.inst=inst;
		this.OP = OP;
		this.r1 = r1;
		this.r2 = r2;
		this.r3 = r3;
		this.ciclos = 0;
		this.depende = null;
		this.tipoDepend = false;
	}
}
