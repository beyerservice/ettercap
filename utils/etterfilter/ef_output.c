/*
    etterfilter -- the actual compiler

    Copyright (C) ALoR & NaGA

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

    $Id: ef_output.c,v 1.1 2003/09/24 19:28:51 alor Exp $
*/

#include <ef.h>
#include <ec_filter.h>

/* protos */

int write_output(void);

/*******************************************/

int write_output(void)
{
   struct filter_op *fop;

   fop = calloc(7, sizeof(struct filter_op));
   
   /* if (DATA.data, search("OpenSSH")) { */
   fop[0].opcode = FOP_FUNC;
   fop[0].op.func.op = FFUNC_SEARCH;
   fop[0].op.func.level = 5;
   strcpy(fop[0].op.func.value, "OpenSSH");
   fop[0].op.func.value_len = strlen(fop[0].op.func.value);
   
   fop[1].opcode = FOP_JFALSE;
   fop[1].op.jmp = 5;

   /* replace("SSH-1.99", "SSH-1.51"); */
   fop[2].opcode = FOP_FUNC;
   fop[2].op.func.op = FFUNC_REPLACE;
   fop[2].op.func.level = 5;
   strcpy(fop[2].op.func.value, "SSH-1.99");
   fop[2].op.func.value_len = strlen(fop[2].op.func.value);
   strcpy(fop[2].op.func.value2, "SSH-1.51");
   fop[2].op.func.value2_len = strlen(fop[2].op.func.value2);
  
   /* msg("SSH downgraded to version 1"); */
   fop[3].opcode = FOP_FUNC;
   fop[3].op.func.op = FFUNC_MSG;
   strcpy(fop[3].op.func.value, "SSH downgraded to version 1");
   
   fop[4].opcode = FOP_JMP;
   fop[4].op.jmp = 6;
   
   /* } else { DATA.data + 3 = '+' */
   fop[5].opcode = FOP_ASSIGN;
   fop[5].op.assign.level = 5;
   fop[5].op.assign.offset = 3;
   fop[5].op.assign.size = 1;
   fop[5].op.assign.value = '+';

   /* } */
   fop[6].opcode = FOP_EXIT;


   return ESUCCESS;
}


/* EOF */

// vim:ts=3:expandtab
