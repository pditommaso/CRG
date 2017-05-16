import groovy.text.*
import java.io.*


params.output_dir = ("$baseDir/output")
params.datasets_directory="$baseDir/benchmark_datasets"
datasets_home= file(params.datasets_directory)
params.score="bengen/baliscore"
params.bucket="50 100 200 300 400 500 600 700 800 900 1000"
params.msa_dir = "MSAs"
params.msa_method ="clustalo_msa" //clustalo_msa, mafft_msa


Channel
  .fromPath("${params.datasets_directory}/${params.dataset}/*.fa")
  .map { tuple( it.baseName, it ) }
  .into{ dataset_fasta }

Channel
  .fromPath("${params.datasets_directory}/${params.dataset}/*.fa.ref")
  .map { tuple( it.name.tokenize('.')[0], it ) }
  .into{ ref_fasta }

Channel.from( "${params.bucket}".tokenize() )
       .into{ bucs }

Channel
   .fromPath("${params.datasets_directory}/${params.dataset}/*.randomtree")
   .map{ tuple( it.baseName, it ) }
   .into{dataset_randomTree}

dataset_fasta.phase(dataset_randomTree)
//      .view()
        .map { tuple(it[0][0], it[0][1], it[1][1])}
        .into {results}

bucs.combine(results)
        //.view()
        .into { data_pairs }
/*
 * Execute an alignment job for each input sequence in the dataset
*/

 process aln {

  tag "${params.msa_method}/${buc}/${id}"
  publishDir "${params.msa_dir}/$buc/$id", mode: 'copy', overwrite: true

  when:
  !file( "${params.msa_dir}/$buc/$id/aln.fa").exists()

  input:
  set buc, id, file(fasta), file(tree)  from data_pairs

  output:
  set id, buc, file('aln.fa') into alignments

  """
  t_coffee -dpa -dpa_method ${params.msa_method} -dpa_tree $tree -seq $fasta -outfile aln.fa  -dpa_nseq $buc -dpa_thread 8 -multicore no
  """

}

ref_fasta.combine(alignments, by: 0)
//      .println()
        .into{ data_aln}

/*
 * Evaluate the alignment score
 */

process score {
    tag "${params.score}/${buc}/${id}"
    container "${params.score}"
    publishDir "${params.msa_dir}/${buc}/${id}", mode: 'move', overwrite: true

    when:
    !file( "${params.msa_dir}/$buc/$id/score.out").exists()

    input:
    set ( id, file(ref), buc,file(aln) ) from data_aln

    output:
    file("score.out")

    """
    t_coffee -other_pg aln_compare -al1 ${ref} -al2 ${aln} | grep -v "seq1" |grep -v '*' | awk '{ print "SOP="\$4}' > score.out
    t_coffee -other_pg aln_compare -al1 ${ref} -al2 ${aln} -compare_mode tc | grep -v "seq1" |grep -v '*' | awk '{ print "TC="\$4}' >> score.out
    """

}

